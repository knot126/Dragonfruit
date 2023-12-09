#include "util/melon.h"
#include "util/storage_filesystem.h"

int DrObfuscateMain(DgArgs *args);
int DrHashMain(DgArgs *args);

int main(int argc, char *argv[]) {
	DgLog(DG_LOG_INFO, "Dragonfruit v0.0.2");
	
	DgInitTime();
	
	DgStorageAddPool(NULL, DgFilesystemCreatePool("file", "."));
	
	DgArgs args;
	
	DgArgParse(&args, argc, argv);
	
	DgArgPrint(&args);
	
	const char *mode = DgArgGetValue2(&args, "m", "help");
	
	if (DgStringEqual(mode, "obfuscate")) {
		return DrObfuscateMain(&args);
	}
	else if (DgStringEqual(mode, "hash")) {
		return DrHashMain(&args);
	}
	else if (DgStringEqual(mode, "help")) {
		DgLog(DG_LOG_INFO, "Usage:");
		DgLog(DG_LOG_INFO, "%s -m <mode> [parameters ...]", argv[0]);
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Generic parameters:");
		DgLog(DG_LOG_INFO, "    -m <mode>              What type of action to preform.");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "OBFUSCATE MODE");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Obfuscate mode parameters:");
		DgLog(DG_LOG_INFO, "    -a <algorithm>         Controls the algorithm encrypt with.");
		DgLog(DG_LOG_INFO, "    -d                     Decrypt for ciphers with differing encrypt and decrypt functions.");
		DgLog(DG_LOG_INFO, "    -p <password>          Password or key used for encryption.");
		DgLog(DG_LOG_INFO, "    -i <input>             Input file path.");
		DgLog(DG_LOG_INFO, "    -o <output>            Output file path.");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Obfuscate mode usage:");
		DgLog(DG_LOG_INFO, "%s -m obfuscate -a <algorithm> [-d] [-p <password>] [-i <input>] [-o <output>]", argv[0]);
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Obfuscate mode algorithms:");
		DgLog(DG_LOG_INFO, "    rot13: The ROT13 shift chipher (latin chars only)");
		DgLog(DG_LOG_INFO, "    cesar: A moboalphabetic cipher");
		DgLog(DG_LOG_INFO, "    poly: The standard polyalphabetic cipher");
		DgLog(DG_LOG_INFO, "    mediocre: Weak encryption algorithm used in games by Mediocre AB");
		DgLog(DG_LOG_INFO, "    sea1: A weak stream cipher based on XORShift");
		DgLog(DG_LOG_INFO, "    sea2: Knot's 2nd Stupid Encryption Algorithm");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "HASH MODE");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Hash mode parameters:");
		DgLog(DG_LOG_INFO, "    -a <algorithm>         Set the hash algorithm to use.");
		DgLog(DG_LOG_INFO, "    -i <input>             Input file to hash.");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Hash mode usage:");
		DgLog(DG_LOG_INFO, "%s -m hash -a <algorithm> [-i <input>]", argv[0]);
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Obfuscate mode algorithms:");
		DgLog(DG_LOG_INFO, "    cubehash256-old: The old variant of CubeHash-256");
		DgLog(DG_LOG_INFO, "    cubehash384-old: The old variant of CubeHash-384");
		DgLog(DG_LOG_INFO, "    cubehash512-old: The old variant of CubeHash-512");
		DgLog(DG_LOG_INFO, "    melon-ch160: 160-bit fast output version of CubeHash in Melon");
		return 1;
	}
	else {
		DgLog(DG_LOG_ERROR, "Invalid mode");
		return 1;
	}
	
	return 0;
}
