
#include <canberra.h>
#include <string>

using namespace std;

namespace Mast {
  namespace TK {
    enum class  SoundEventType {
      Ok,
	Fail,
	EmptyTrash,
	Logout,
	Login
    };

    static std::string getSoundName(SoundEventType soundType){
      switch(soundType){
      case SoundEventType::Ok:
	return "dialog-information";
      case SoundEventType::Fail:
	return "dialog-error";
      case SoundEventType::EmptyTrash:
	return "empty-trash";
      case SoundEventType::Logout:
	return "system-log-out";
      case SoundEventType::Login:
	return "system-log-in";
      default:
	return "";
      }
    }

    class SoundEvent{
    private:
      SoundEventType evt_type;
      std::string description;
    public:
      SoundEvent(SoundEventType evtType, std::string desc);
      ~SoundEvent();
      void run();
    };

    
  }
}
void trigger_sound(Mast::TK::SoundEventType t, std::string d);

#define TRIGGER_MAST_SOUND (t,d) trigger_sound(t,d)
