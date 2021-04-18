
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
  startY = 6;
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
      set_field_back(fields.at(indices[name]), it->first);
    } else {
      if(it->second){
	field_opts_on(fields.at(indices[name]), it->first);
      } else {
	field_opts_off(fields.at(indices[name]), it->first);
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
  set_field_just(fields.at(indices[name]), justMode);
}

void Mast::TK::Form::addField(string name){
  int position = this->fields.size();
  this->fields.push_back(new_field(1, this->width, this->startY + (position * 2), this->startX + 20, 0, 0));
  this->indices[name] = position;
  this->names[position] = name;
  this->labels[this->fields[position]] = "";
  this->password_fields[name] = false;
}

string Mast::TK::Form::getLabel(string name) {
  return this->labels[fields.at(indices[name])];
}

string Mast::TK::Form::getLabel(int i) {
  return this->labels[this->getFieldAt(i)];
}

void Mast::TK::Form::setLabel(string name, string label){
  this->labels[fields.at(indices[name])] = label;
}

void Mast::TK::Form::setLabel(int i,  string label) {
  this->labels[this->getFieldAt(i)] = label;
}

bool Mast::TK::Form::validate(Mast::TK::DataMap subVal){
  for (auto it = this->submission_constraints.begin(); it != this->submission_constraints.end(); ++it){
    Mast::TK::Validator validity = it->second;
    auto it2 = subVal.find(it->first);
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
  Mast::TK::DataMap subVal =  this->values;
  this->onSubmit(subVal,validate(subVal));
}

void Mast::TK::Form::draw(){
  this->currentField = 0;
  this->fields.push_back(NULL);
  if(this->wind != nullptr)
    this->wind->draw();
  int rows, cols;
  this->form = new_form(this->fields.data());
  scale_form(this->form, &rows, &cols);
  if(this->wind != nullptr){
    set_form_win(this->form, this->wind->getWindow());
    WINDOW* sub_win = derwin(this->wind->getWindow(), rows, cols, 2, 2);
    set_form_sub(this->form, sub_win);
    this->wind->toggle_keypad(true);
    post_form(this->form);
    int i = 0;
    for (auto it = this->labels.begin(); it != this->labels.end(); ++it){
      mvwprintw(sub_win, this->startY + (2 * i), this->startX - 10, it->second.c_str());
      i++;
    }
    wrefresh(this->wind->getWindow());
    refresh();
  }
}

Mast::TK::Form::~Form(){
  unpost_form(this->form);
  free_form(this->form);
  for (int i = 0; i < fields.size(); ++i)
    free_field(fields.at(i));
}

const int BACK = 127;
const int ENTER = 10;

void Mast::TK::Form::setPasswordEnabled(string name, bool use_pwd){
  this->password_fields[name] = use_pwd;
  this->passwds[name] = "";
}

bool Mast::TK::Form::checkPassword(string name, int c){
  if (this->password_fields[name]){
    if(c == BACK){
      if(this->passwds[name].size() != 0){
	this->passwds[name].resize(this->passwds[name].size() - 1);
	this->values[name] = this->passwds[name];
	form_driver(this->form, REQ_DEL_PREV);
	return true;
      }
    } else {
	this->passwds[name] += c;
	this->values[name] = this->passwds[name];
	form_driver(this->form, '*');
	return true;
    }
    
  }
  return false;
}

string Mast::TK::Form::getCurrentFieldName() const {
  auto it = names.find(currentField);
  if(it != names.end())
    return it->second;
  return "";
}

void Mast::TK::Form::processInput(int c){
  switch(c){
  case KEY_DOWN:
    form_driver(this->form, REQ_NEXT_FIELD);
    form_driver(this->form, REQ_END_LINE);
    if(currentField < (fields.size() - 1))
      currentField++;
    break;
  case KEY_UP:
    form_driver(this->form, REQ_PREV_FIELD);
    form_driver(this->form, REQ_END_LINE);
    if(currentField > 0)
      currentField--;
    break;
  case KEY_F(5):
    // submit key.
    this->submit();
    break;
  default:
    if(!this->checkPassword(this->getCurrentFieldName(), c)){
      if(c == 127){
	this->values[this->getCurrentFieldName()].resize(this->values[this->getCurrentFieldName()].size() - 1);
	form_driver(this->form, REQ_DEL_PREV);
	return;
      }
      this->values[this->getCurrentFieldName()] += (char)c;
      form_driver(this->form, c);
    }
    break;
  }
}
