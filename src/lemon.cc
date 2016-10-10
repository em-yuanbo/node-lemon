#include <nan.h>
#include <string.h>
//extern "C"{
#include "lemon/sqliteInt.h"
//}
//extern "C"{
  //extern int sqlite3RunParser(Parse *pParse, const char *zSql, char **pzErrMsg);
//}

using namespace v8;
v8::Local<v8::Object> toJSON(Parse * parseObj);

void ParseSql(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if(info.Length()<2){
    Nan::ThrowTypeError("Wrong number of arguments");
  }
  if(!info[0]->IsString()||!info[1]->IsFunction()){
    Nan::ThrowTypeError("Wrong arguments");
  }
  /*
   * do parse and get result
   *
   */
  Parse parseObj;
  char* errMsg = 0;
  memset(&parseObj, 0, sizeof(parseObj));

  Nan::Utf8String nan_string(info[0]->ToString());
  std::string cc_string(*nan_string);
  const char * c_sql = cc_string.c_str();
  sqlite3RunParser(&parseObj,c_sql, &errMsg);

  if( sqlite3MallocFailed()  ){
    parseObj.rc = SQLITE_NOMEM;
  }
  if( parseObj.rc==SQLITE_DONE ) parseObj.rc = SQLITE_OK;

  v8::Local<v8::Function> cb = info[1].As<v8::Function>();
  const unsigned argc = 2;

  //v8::Local<v8::Value> argv[argc] = { Nan::Null(),Nan::New("hello world").ToLocalChecked() };
  //
  //v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  v8::Local<v8::Object> obj = toJSON(&parseObj);
  obj->Set(Nan::New("src").ToLocalChecked(),info[0]->ToString());


  v8::Local<v8::Value> err= Nan::Null();
  if(errMsg!=NULL){
    err = Nan::Error(errMsg);
  }
  v8::Local<v8::Value> argv[argc]= { err, obj };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}

v8::Local<v8::Object> toJSON(Parse * parseObj){
  int size = parseObj->parsed.curSize;
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  ParsedResultArray parsed = parseObj->parsed;
  v8::Local<v8::Array> statementArray = Nan::New<v8::Array>();
  int i = 0;
  ParsedResultItem* pStatement = parsed.array;
  while(i<size){
    v8::Local<v8::Object> statementObj= Nan::New<v8::Object>();

    statementObj->Set(Nan::New("type").ToLocalChecked(),Nan::New(pStatement->sqltype));
    statementArray->Set(i,statementObj);

    i++;
    pStatement++;
  }
  obj->Set(Nan::New("statements").ToLocalChecked(),statementArray);
  return obj;
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("parse").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(ParseSql)->GetFunction());
}


NODE_MODULE(lemon, Init);
