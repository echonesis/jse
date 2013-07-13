#define JSNativeValueSource

#include "JSNative.h"

JSClassRef JSNativeValue = NULL;
JSObjectRef RtJSNativeValue = NULL;

static JSObjectRef Construct JSTNativeConstructor () {
	JSObjectRef this = JSTCreateClassObject(JSNativeValue, NULL);
	JSValueRef type; JSValueRef size = JSTGetProperty((JSObjectRef) (type = (JSObjectRef) JSNativeTypeDeref(JSTParam(1))), "size");
	if (JSTReference(type)) {
		JSTSetProperty(this, "type", type, JSTPropertyRequired);
		JSTSetProperty(this, "count", JSTParam(2), JSTPropertyRequired);
		JSTSetProperty(this, "address", JSTCall(RtJSNativeAllocatorLease, RtJSNativeAllocator, size, JSTParam(2)), JSTPropertyRequired);
		return this;
	} else {
		return NULL;
	}
}

static JSValueRef GetProperty JSTNativePropertyReader() {
	JSValueRef index = JSTEval("parseInt(this)", JSTMakeString(property, NULL, false));
	if (JSTBoolean(JSTCall(RtJSObject(isNaN), NULL, index))) return NULL;
	long offset = JSTInteger(index);
	printf("requested index: %i", offset);
	return RtJS(undefined);
}

static bool SetProperty JSTNativePropertyWriter() {
	return false;
}

static JSValueRef Convert JSTNativeConvertor() {
	if (type == JSTNumberType) return JSTGetProperty(object, "address");
	return NULL;
}

void js_native_value_init JSToolsProcedure(JSObjectRef object) {

	JSClassDefinition jsNative = kJSClassDefinitionEmpty;
	jsNative.className = "JSNative.Value";
	jsNative.attributes = kJSClassAttributeNoAutomaticPrototype;
	jsNative.callAsConstructor = &Construct;
	jsNative.setProperty = &SetProperty;
	jsNative.getProperty = &GetProperty;
	jsNative.convertToType = &Convert;
	JSStaticValue StaticValueArray[] = {
		{ "name",		&GetProperty, NULL, JSTPropertyConst },
		{ "code",		&GetProperty, NULL, JSTPropertyConst },
		{ "size",		&GetProperty, NULL, JSTPropertyConst },
		{ "maximum",	&GetProperty, NULL, JSTPropertyConst },
		{ "minimum",	&GetProperty, NULL, JSTPropertyConst },
		{ "integral",	&GetProperty, NULL, JSTPropertyConst },
		{ 0, 0, 0, 0 }
	};

	jsNative.staticValues = StaticValueArray;
	JSNativeValue = JSClassRetain(JSClassCreate(&jsNative));

	RtJSNativeValue = JSTMakeConstructor(JSNativeValue, &Construct);

	JSTSetProperty(object, "Value", RtJSNativeValue, JSTPropertyConst);


}
