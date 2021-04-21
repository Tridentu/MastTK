#include <canberra.h>
#include <cstdlib>
#include "MastSoundEvent.h"

Mast::TK::SoundEvent::SoundEvent(Mast::TK::SoundEventType evtType, std::string desc){
  this->evt_type = evtType;
  this->description = desc;
}

Mast::TK::SoundEvent::~SoundEvent(){
  
}

void Mast::TK::SoundEvent::run(){
  std::string eventSound("canberra-gtk-play -i ");
  eventSound += getSoundName(this->evt_type);
  eventSound += " -d \"";
  eventSound += this->description;
  eventSound += "\"";
  system(eventSound.c_str());
}

void trigger_sound(Mast::TK::SoundEventType t, std::string d){
  Mast::TK::SoundEvent* event = new Mast::TK::SoundEvent(t,d);
  event->run();
}
