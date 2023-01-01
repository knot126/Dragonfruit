#include "util/log.h"
#include "util/obfuscate.h"
#include "util/string.h"

int main(int argc, char *argv[]) {
	DgLog(DG_LOG_INFO, "Dragonfruit v0.0.1");
	
	char buf[] = "This is a string of text that will be shifted using a Mediocre AB-compatible obfuscation algorithm.";
	size_t len = DgStringLength(buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
	
	DgPolyalphabeticObfuscate("key", 0, len, buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
	
	DgPolyalphabeticDeobfuscate("key", 0, len, buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
	
	return 0;
}
