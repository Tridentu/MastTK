
#include <libnotify/notify.h>
#include <string>

namespace MastTDE {
  class NotificationPinger {
  public:
    NotificationPinger(std::string name);
    ~NotificationPinger();
    void Ping(std::string title, std::string message, std::string type = "dialog-information");
  private:
    std::string m_Name;
    NotifyNotification* m_Notification;
  };
}
