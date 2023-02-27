#include "util/log.h"
#include "util/obfuscate.h"
#include "util/string.h"
#include "util/storage_filesystem.h"
#include "util/file.h"
#include "util/args.h"

int main(int argc, char *argv[]) {
	DgLog(DG_LOG_INFO, "Dragonfruit v0.0.1");
	
	DgStorageAddPool(NULL, DgFilesystemCreatePool("file", "."));
	
	DgArgs args;
	
	DgArgParse(&args, argc, argv);
	
	DgArgPrint(&args);
	
	const char *file_in = DgArgGetValue2(&args, "i", "file://input.dat");
	const char *file_out = DgArgGetValue2(&args, "o", "file://output.dat");
	const char *algorithm = DgArgGetValue2(&args, "a", "none");
	const char *password = DgArgGetValue2(&args, "p", "password");
	bool decrypt = DgArgGetFlag(&args, "d");
	
	DgObfuscateAlgorithm algorithm_id;
	
	if (DgStringEqual(algorithm, "rot13")) {
		algorithm_id = DG_OBFUSCATE_ROT13;
	}
	else if (DgStringEqual(algorithm, "cesar")) {
		algorithm_id = DG_OBFUSCATE_CESAR;
	}
	else if (DgStringEqual(algorithm, "poly")) {
		algorithm_id = DG_OBFUSCATE_POLYALPHABETIC;
	}
	else if (DgStringEqual(algorithm, "mediocre")) {
		algorithm_id = DG_OBFUSCATE_MEDIOCRE;
	}
	else if (DgStringEqual(algorithm, "sea1")) {
		algorithm_id = DG_OBFUSCATE_SEA1;
	}
	else if (DgStringEqual(algorithm, "sea2")) {
		algorithm_id = DG_OBFUSCATE_SEA2;
	}
	else {
		DgLog(DG_LOG_INFO, "Usage:");
		DgLog(DG_LOG_INFO, "dragonfruit -a <algorithm> [-d] [-p <password>] [-i <input>] [-o <output>]");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "    -a <algorithm>         Controls the algorithm encrypt with.");
		DgLog(DG_LOG_INFO, "    -d                     Decrypt for ciphers with differing encrypt and decrypt functions.");
		DgLog(DG_LOG_INFO, "    -p <password>          Password or key used for encryption.");
		DgLog(DG_LOG_INFO, "    -i <input>             Input file path.");
		DgLog(DG_LOG_INFO, "    -o <output>            Output file path.");
		DgLog(DG_LOG_INFO, "");
		DgLog(DG_LOG_INFO, "Available encryption algorithms:");
		DgLog(DG_LOG_INFO, "    rot13: The ROT13 shift chipher (latin chars only)");
		DgLog(DG_LOG_INFO, "    cesar: A moboalphabetic cipher");
		DgLog(DG_LOG_INFO, "    poly: The standard polyalphabetic cipher");
		DgLog(DG_LOG_INFO, "    mediocre: Weak encryption algorithm used in games by Mediocre AB");
		DgLog(DG_LOG_INFO, "    sea1: A weak stream cipher based on XORShift");
		DgLog(DG_LOG_INFO, "    sea2: Knot's 2nd Stupid Encryption Algorithm");
		DgLog(DG_LOG_INFO, "");
		
		DgLog(DG_LOG_ERROR, "You did not specify any algorithm!");
		return 1;
	}
	
	DgLog(DG_LOG_INFO, "Input file: %s", file_in);
	DgLog(DG_LOG_INFO, "Output file: %s", file_out);
	
	// Load the file
	DgError status;
	size_t length;
	void *data;
	
	status = DgFileLoad(NULL, file_in, &length, &data);
	
	if (status) {
		DgLog(DG_LOG_FATAL, "Failed to load input file!");
		return 1;
	}
	
	DgLog(DG_LOG_INFO, "Loaded file...");
	
	if (!decrypt) {
		DgObfuscateData(algorithm_id, password, length, data);
	}
	else {
		DgDeobfuscateData(algorithm_id, password, length, data);
	}
	
	DgLog(DG_LOG_INFO, "Data transformed...");
	
	status = DgFileSave(NULL, file_out, length, data);
	
	if (status) {
		DgLog(DG_LOG_FATAL, "Failed to save output file! (status = 0x%x)", status);
		return 1;
	}
	
	DgLog(DG_LOG_INFO, "Saved file...");
	
	DgArgFree(&args);
	
	return 0;
}
