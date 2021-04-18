// MastTK Forms
#pragma once
#include <curses.h>
#include <form.h>
#include <vector>
#include <map>
#include <cstring>
#include <cstdio>
#include <any>
#include <functional>
#include "MastWindow.h"
using namespace std;

namespace Mast {
  namespace TK {
    typedef std::map<string, int> IndexMap;
    typedef std::vector<FIELD*> FieldVector;
    typedef std::map<string, FIELDTYPE*> BValidationMap;
    typedef std::map<int, bool> FieldAttrMap;
    typedef std::vector<char*> FieldPtrVector;
    typedef std::function<bool(std::any)> Validator;
    typedef std::map<string, Validator> AValidationMap;
    typedef std::map<string, string> DataMap;
    typedef std::function<bool(DataMap,bool)> ProcessorCallback;
    typedef std::map<FIELD*, string> LabelMap;
    typedef std::map<string, bool> PasswordBoolMap;
    typedef std::map<string, string> PasswordMap;
    typedef std::map<int, string> ReversedIndexMap;
    class Form {
    protected:
      FieldVector fields;
      IndexMap indices;
      FieldPtrVector pointers;
      AValidationMap submission_constraints;
      BValidationMap constraints;
      DataMap values;
      FORM* form;
      LabelMap labels;
      int startX;
      int startY;
      int width;
      Window* wind;
      PasswordBoolMap password_fields;
      PasswordMap passwds;
      ReversedIndexMap names;
      int currentField;
    public:
      ProcessorCallback onSubmit;
      
    public:
      FIELD* getFieldAt(int i);
      FIELD* operator[](string name) { return fields.at(indices[name]); };
      void setAttributes(string name, bool setBack, const FieldAttrMap map);
      void setAttributes(int i, bool setBack, const FieldAttrMap map);
      void justifyField(int i, int justMode);
      void justifyField(string name, int justMode);
      void addField(string name);
      string getLabel(string name);
      string getLabel(int i);
      void setLabel(string name, string label);
      void setLabel(int i, string label);
      void submit();
      void draw();
      bool validate(DataMap subVal);
      void setOnSubmitCallback(ProcessorCallback cb);
      Form();
      Form(Window* win);
      Form(Window* win, int width0, int startX0, int startY0, FieldVector initFields);
      ~Form();
      bool checkPassword(string name, int c);
      void setPasswordEnabled(string name, bool use_pwd);
      void processInput(int c);
      string getCurrentFieldName() const;
    };
  }
}
  
