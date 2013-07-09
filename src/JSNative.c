/* Brigadier */
#include <stdio.h>

#define JSNativeSource

#include "JSNative.inc"

#include "JSNative.h"

JSObjectRef RtJSNative = NULL;

void js_native_init JSToolsProcedure (int argc, char *argv[], char *envp[]) {

	JSObjectRef global = JSTGetGlobalObject();

	JSTLoadRuntime(global, argc, argv, envp);

	/* our root object */
	JSTSetProperty(global, "JSNative", (RtJSNative = JSTCreateClassObject(NULL, NULL)), JSTPropertyConst);

	JSTEval(JSNativeSupport, global);

}

