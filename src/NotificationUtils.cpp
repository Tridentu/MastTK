

#include "NotificationUtils.h"

namespace MastTDE {
  NotificationPinger::NotificationPinger(std::string name){
    notify_init(name.c_str());
  };

  void NotificationPinger::Ping(std::string title, std::string message, std::string type){
    m_Notification = notify_notification_new(title.c_str(),message.c_str(),type.c_str());
    notify_notification_show(m_Notification, NULL);
    delete this;
  };

  NotificationPinger::~NotificationPinger(){
    g_object_unref(G_OBJECT(m_Notification));
    notify_uninit();
  };
  
}
