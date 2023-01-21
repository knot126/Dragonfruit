#include "util/log.h"
#include "util/obfuscate.h"
#include "util/string.h"
#include "util/file.h"

void polyalphabetic(void) {
	/**
	 * Polyalphabetic
	 */
	
	char buf[] = "This is a string of text that will be shifted using a Mediocre AB-compatible obfuscation algorithm.";
	size_t len = DgStringLength(buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
	
	DgPolyalphabeticObfuscate("key", 0, len, buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
	
	DgPolyalphabeticDeobfuscate("key", 0, len, buf);
	
	DgLog(DG_LOG_INFO, "%s", buf);
}

int main(int argc, char *argv[]) {
	DgLog(DG_LOG_INFO, "Dragonfruit v0.0.1");
	
	char buf[] = "Encrypted using probably a shitty encryption algorithm..";
	
	DgLog(DG_LOG_VERBOSE, "%s", buf);
	
	DgObfuscateXorShiftShift("kekko", DgStringLength(buf), buf);
	
	DgLog(DG_LOG_VERBOSE, "%s", buf);
	
	DgFileSave(NULL, "./data.dat", DgStringLength(buf), buf);
	
	DgObfuscateXorShiftShift("kekko", DgStringLength(buf), buf);
	
	DgLog(DG_LOG_VERBOSE, "%s", buf);
	
	DgLog(DG_LOG_SUCCESS, "Done");
	
	return 0;
}
