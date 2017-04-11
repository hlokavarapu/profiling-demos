#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include <deal.II/base/timer.h>
#include <fstream>

class EventLog
{
public:
  ~EventLog()
  {
    reset(NULL);
  }

  void reset(const char* filename)
  {
    f << "{ \"type\": \"dummy\"}" << std::endl;
    f << "]}" << std::endl;
    f.close();
    timer.reset();
    timer.start();
    if (filename)
      {
        f.open(filename);
        f << "{\"events\": [" << std::endl;
      }
  }

  unsigned int log_begin(const char* event_name)
  {
    double start = timer.wall_time();
    ++event_id;
    f << "{ \"type\": \"start\""
      << ", \"id\": " << event_id
      << ", \"time\": " << start
      << ", \"name\": \"" << event_name << "\"},\n";
    return event_id;
  }

  void log_end(unsigned int event_id)
  {
    double t = timer.wall_time();
    f << "{ \"type\": \"end\""
      << ", \"time\": " << t
      << ", \"id\": " << event_id
      << "},\n";
  }

  void log_once(const char* event_name)
  {
    ++event_id;
    double t = timer.wall_time();
    f << "{ \"type\": \"once\""
      << ", \"time\": " << t
      << ", \"id\": " << event_id
      << ", \"name\": \"" << event_name << "\""
      << "},\n";
  }


  class Scope
  {
  public:
    Scope(EventLog &eventlog, const char* event_name)
      : eventlog(eventlog)
    {
      id = eventlog.log_begin(event_name);
    }
    ~Scope()
    {
      eventlog.log_end(id);
    }

  private:
    EventLog &eventlog;
    unsigned int id;
  };

private:
  double start;
  unsigned int event_id;
  std::ofstream f;
  dealii::Timer timer;
};


#endif
