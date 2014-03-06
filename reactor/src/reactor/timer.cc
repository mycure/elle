#include <reactor/timer.hh>

#include <boost/asio.hpp>

#include <elle/finally.hh>
#include <elle/log.hh>

#include <reactor/duration.hh>
#include <reactor/thread.hh>
#include <reactor/scheduler.hh>
#include <reactor/Barrier.hh>


ELLE_LOG_COMPONENT("reactor.Timer")

namespace reactor
{
  Timer::Timer(const std::string& name,
    Duration d,
    const Action& action)
  : Timer(*Scheduler::scheduler(), name, d, action)
  {}

  Timer::Timer(Scheduler& s,
    const std::string& name,
    Duration d,
    const Action& action)
  : _scheduler(s)
  , _name(name)
  , _action(action)
  , _timer(s.io_service())
  {
    _timer.expires_from_now(d);
    _timer.async_wait(std::bind(&Timer::_on_timer, this, std::placeholders::_1));
  }

  Timer::~Timer()
  {
    ELLE_TRACE("%s destructor", *this);
    cancel_now();
  }

  void Timer::_on_timer(const boost::system::error_code& erc)
  {
    ELLE_TRACE("%s timer reached, canceled=%s", *this, !!erc);
    // Warning, we are not in a Thread!
    if (!erc)
    {
      _thread.reset(new Thread(_scheduler, _name,
        [this]
        {
          elle::SafeFinally s([this]
            {
              ELLE_TRACE("%s timer interrupted or finished, notifying", *this);
              this->_barrier.open();
            });
          ELLE_TRACE("%s timer invoking callback", *this);
          this->_action();
        }));
    }
    else
      this->_barrier.open();
  }

  void Timer::cancel()
  {
    _timer.cancel();
  }

  void Timer::cancel_now()
  {
    this->cancel();
    ELLE_DUMP("%s waiting...", *this);
    if (!this->_barrier)
      this->_barrier.wait();
    // Waiting on the barrier is not enough as it gets opened from
    // the thread. We must wait for the thread itself.
    if (this->_thread && !this->_thread->done())
      reactor::wait(*this->_thread);
    ELLE_DUMP("%s waiting done", *this);
  }

  void Timer::terminate()
  {
    this->cancel();
    if (_thread)
      _thread->terminate();
  }

  void Timer::terminate_now(bool suicide)
  {
    this->cancel();
    if (_thread)
      _thread->terminate_now(suicide);
  }

  // waitable interface
  bool Timer::_wait(Thread* thread)
  {
    ELLE_DUMP("%s wait called, forwarding", *this);
    thread->wait(_barrier);
    ELLE_DUMP("%s wait returned", *this);
    return false;
  }
}
