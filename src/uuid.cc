#include <v8.h>
#include <node.h>
#include <nan.h>
#include <uuid/uuid.h>

#undef UUID_STR_LEN
#define UUID_STR_LEN 36

static inline void my_uuid_unparse_lower(uuid_t in, char *out) {
  int i;
  uuid_unparse(in, out);
  for(i=0;i<36;i++) out[i] = tolower(out[i]);
}

using namespace v8;
using namespace node;

void Create(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  uuid_t id;
  char uuid_str[37];

  uuid_generate(id);
  my_uuid_unparse_lower(id, uuid_str);

  info.GetReturnValue().Set(Nan::New(uuid_str).ToLocalChecked());
}


void init(Handle<Object> exports) {
  exports->Set(Nan::New("create").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(Create)->GetFunction());
}
NODE_MODULE(uuid, init)
