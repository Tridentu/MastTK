
#include <curses.h>
#include <form.h>
#include <vector>
#include <map>
#include <cstring>
#include <any>
#include <cstdio>
#include <functional>
#include "MastWindow.h"
#include "MastForm.h"

using namespace std;

Mast::TK::Form::Form(){
  startX = 15;
  startY = 4;
  width = 25;
  
}

Mast::TK::Form::Form(Window* win){
  startX = 15;
  startY = 4;
  width = 25;
  wind = win;
}

Mast::TK::Form::Form(Window* win, int width0, int startX0, int startY0, FieldVector initFields){
  this->startX = startX0;
  this->startY = startY0;
  this->width = width0;
  this->fields = initFields;
  this->wind = win;
}

FIELD* Mast::TK::Form::getFieldAt(int i){
  return this->fields.at(i);
}

void Mast::TK::Form::setAttributes(string name, bool setBack, const FieldAttrMap map){
  for(auto it = map.begin(); it != map.end(); ++it){
    if(setBack){
      if(!it->second)
	continue;
      set_field_back(this[name], it->first);
    } else {
      if(it->second){
	field_opts_on(this[name], it->first);
      } else {
	field_opts_off(this[name], it->first);
      }
    }
  }
}

void Mast::TK::Form::setAttributes(int i, bool setBack, const FieldAttrMap map){
  for(auto it = map.begin(); it != map.end(); ++it){
    if(setBack){
      if(!it->second)
	continue;
      set_field_back(this->getFieldAt(i), it->first);
    } else {
      if(it->second){
	field_opts_on(this->getFieldAt(i), it->first);
      } else {
	field_opts_off(this->getFieldAt(i), it->first);
      }
    }
  }
}

void Mast::TK::Form::justifyField(int i, int justMode){
  set_field_just(this->getFieldAt(i), justMode);
}

void Mast::TK::Form::justifyField(string name, int justMode){
  set_field_just(this[name], justMode);
}

void Mast::TK::Form::addField(string name, int position){
  this->fields[position] = new_field(1, this->width, this->startY + (position * 2), 0, 0);
  this->indices[name] = position;
  this->labels[this->fields[position]] = "";
}

string Mast::TK::Form::getLabel(string name) const {
  return this->labels[this[name]];
}

string Mast::TK::Form::getLabel(int i) const {
  return this->labels[this->getFieldAt(i)];
}

void Mast::TK::Form::setLabel(string name, string label){
  this->labels[this[name]] = label;
}

void Mast::TK::Form::setLabel(int i,  string label) {
  this->labels[this->getLabelAt(i)] = label;
}

bool Mast::TK::Form:validate(DataMap subVal){
  for (auto it = this->submission_constraints.begin(); it != this->submission_constraints.end(); ++it){
    Mast::TK::Validator validity = it->second;
    auto it2 = subVal->find(it->first);
    if (it2 == subVal.end())
      continue;
    if(!validity(it2->second))
      return false;
  }
  return true;
}

void  Mast::TK::Form::setOnSubmitCallback( Mast::TK::ProcessorCallback cb){
  this->onSubmit = cb;
}

void Mast::TK::Form::submit(){
  DataMap subVal - this->values;
  this->onSubmit(subVal,validate(subVal));
}

void Mast::TK::Form::draw(){
  this->fields[this->fields.size()] = NULL;
  if(this->wind != nullptr)
    this->wind->draw();
  int rows, cols;
  this->form = new_form(this->fields->data());
  scale_form(this->form, &rows, &cols);
  if(this->wind != nullptr){
    set_form_win(this->form, this->wind->getWindow());
    set_form_sub(this->form, derwin(this->wind->getWindow(), rows, cols, 2, 2));
    this->wind->setKeyboard(this->wind->getWindow(), 0, 0);
    post_form(this->form);
    wrefresh(this->wind->getWindow());
  }
}

Mast::TK::Form::~Form(){
  unpost_form(this->form);
  free_form(this->form);
  for (int i = 0; i < fields.size(); ++i)
    free_field(fields.at(i));
}
