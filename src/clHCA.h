#pragma once

//--------------------------------------------------
// HCA (High Compression Audio) class
//--------------------------------------------------
class clHCA {
public:
	clHCA(unsigned int ciphKey1 = 0xE0748978, unsigned int ciphKey2 = 0xCF222F1F);

	// HCA check
	static bool CheckFile(void *data, unsigned int size);

	// Checksum
	static unsigned short CheckSum(void *data, int size, unsigned short sum = 0);

	// Console output header information
	bool PrintInfo(const char *filenameHCA);

	// Decryption
	bool Decrypt(const char *filenameHCA);

	// Decode and save to WAVE file
	bool DecodeToWavefile(const char *filenameHCA, const char *filenameWAV, float volume = 1, int mode = 16, int loop = 0);
	bool DecodeToWavefileStream(void *fpHCA, const char *filenameWAV, float volume = 1, int mode = 16, int loop = 0);

	// Encode and save to HCA file
	//bool EncodeFromWavefile(const char *filenameWAV,const char *filenameHCA,float volume=1);
	//bool EncodeFromWavefileStream(void *fpWAV,const char *filenameHCA,float volume=1);

private:
	struct stHeader {// File information (required)
		unsigned int hca;              // 'HCA'
		unsigned short version;        // Version. v1.3 and v2.0 are the known versions
		unsigned short dataOffset;     // Data offset
	};
	struct stFormat {//Format information (required)
		unsigned int fmt;              // 'fmt'
		unsigned int channelCount : 8;   // Number of channels 1 to 16
		unsigned int samplingRate : 24;  // Sampling rate 1 to 0x7FFFFF
		unsigned int blockCount;       // Block count 0 or more
		unsigned short muteHeader;     // First silent part (number of blocks * 0x400+0x80)
		unsigned short muteFooter;     // Number of silent samples at the end
	};
	struct stCompress {// Compression information (either compressed information or decode information is mandatory)
		unsigned int comp;             // 'comp'
		unsigned short blockSize;      // Block size (valid for CBR?) 8 to 0xFFFF, 0 means VBR
		unsigned char r01;             // Unknown(1) 0〜r02      v2.0 Currently only 1 supported
		unsigned char r02;             // Unknown(15) r01〜0x1F  v2.0 Currently only 15 supported
		unsigned char r03;             // Unknown(1)(1)
		unsigned char r04;             // Unknown(1)(0)
		unsigned char r05;             // Unknown(0x80)(0x80)
		unsigned char r06;             // Unknown(0x80)(0x20)
		unsigned char r07;             // Unknown(0)(0x20)
		unsigned char r08;             // Unknown(0)(8)
		unsigned char reserve1;        // Reserved
		unsigned char reserve2;        // Reserved
	};
	struct stDecode {// Decode information (either compressed information or decode information is mandatory)
		unsigned int dec;              // 'dec'
		unsigned short blockSize;      // Block size (valid for CBR?) 8 to 0xFFFF, 0 means VBR
		unsigned char r01;             // Unknown(1) 0〜r02      v2.0 Currently only 1 supported
		unsigned char r02;             // Unknown(15) r01〜0x1F  v2.0 Currently only 15 supported
		unsigned char count1;          // Number of type0 and type1-1
		unsigned char count2;          // Number of type2-1
		unsigned char r03 : 4;           // Unknown(0)
		unsigned char r04 : 4;           // Unknown(0) 0 is modified to 1
		unsigned char enableCount2;    // Flag using count2
	};
	struct stVBR {// Variable bit rate information (obsolete?)
		unsigned int vbr;              // 'vbr'
		unsigned short r01;            // Unknown 0〜0x1FF
		unsigned short r02;            // Unknown
	};
	struct stATH {// ATH table information (obsolete since v2.0)?
		unsigned int ath;              // 'ath'
		unsigned short type;           // Type of table(0:All 0 1:Table1)
	};
	struct stLoop {// Loop information
		unsigned int loop;             // 'loop'
		unsigned int start;            // Loop start block index 0 - loopEnd
		unsigned int end;              // Loop end block index loopStart〜(stFormat::blockCount-1)
		unsigned short count;          // Loop count 0x80 Infinite loop
		unsigned short r01;            // Unknown(0x226) 
	};
	struct stCipher {// Cryptographic table information
		unsigned int ciph;             // 'ciph'
		unsigned short type;           // Type of encryption (0: no encryption 1: keyless encryption 0x38: keyed encryption
	};
	struct stRVA {// Relative volume adjustment information
		unsigned int rva;              // 'rva'
		float volume;                  // volume
	};
	struct stComment {// Comment
		unsigned int comm;             // 'comm'
		unsigned char len;             // Comment length?
		//char comment[];
	};
	struct stPadding {// Padding
		unsigned int pad;              // 'pad'
	};
	unsigned int _version;
	unsigned int _dataOffset;
	unsigned int _channelCount;
	unsigned int _samplingRate;
	unsigned int _blockCount;
	unsigned int _muteHeader;
	unsigned int _muteFooter;
	unsigned int _blockSize;
	unsigned int _comp_r01;
	unsigned int _comp_r02;
	unsigned int _comp_r03;
	unsigned int _comp_r04;
	unsigned int _comp_r05;
	unsigned int _comp_r06;
	unsigned int _comp_r07;
	unsigned int _comp_r08;
	unsigned int _comp_r09;
	unsigned int _vbr_r01;
	unsigned int _vbr_r02;
	unsigned int _ath_type;
	unsigned int _loopStart;
	unsigned int _loopEnd;
	unsigned int _loopCount;
	unsigned int _loop_r01;
	bool _loopFlg;
	unsigned int _ciph_type;
	unsigned int _ciph_key1;
	unsigned int _ciph_key2;
	float _rva_volume;
	unsigned int _comm_len;
	char *_comm_comment;
	class clATH {
	public:
		clATH();
		bool Init(int type, unsigned int key);
		unsigned char *GetTable(void);
	private:
		unsigned char _table[0x80];
		void Init0(void);
		void Init1(unsigned int key);
	}_ath;
	class clCipher {
	public:
		clCipher();
		bool Init(int type, unsigned int key1, unsigned int key2);
		void Mask(void *data, int size);
	private:
		unsigned char _table[0x100];
		void Init0(void);
		void Init1(void);
		void Init56(unsigned int key1, unsigned int key2);
		void Init56_CreateTable(unsigned char *table, unsigned char key);
	}_cipher;
	class clData {
	public:
		clData(void *data, int size);
		int CheckBit(int bitSize);
		int GetBit(int bitSize);
		void AddBit(int bitSize);
	private:
		unsigned char *_data;
		int _size;
		int _bit;
	};
	struct stChannel {
		float block[0x80];
		float base[0x80];
		char value[0x80];
		char scale[0x80];
		char value2[8];
		int type;
		char *value3;
		unsigned int count;
		float wav1[0x80];
		float wav2[0x80];
		float wav3[0x80];
		float wave[8][0x80];
		void Decode1(clData *data, unsigned int a, int b, unsigned char *ath);
		void Decode2(clData *data);
		void Decode3(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
		void Decode4(int index, unsigned int a, unsigned int b, unsigned int c);
		void Decode5(int index);
	}_channel[0x10];
	bool Decode(void *data, unsigned int size, unsigned int address);
	bool DecodeToWavefile_Decode(void *fp1, void *fp2, unsigned int address, unsigned int count, void *data, void *modeFunction);
	static void DecodeToWavefile_DecodeModeFloat(float f, void *fp);
	static void DecodeToWavefile_DecodeMode8bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode16bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode24bit(float f, void *fp);
	static void DecodeToWavefile_DecodeMode32bit(float f, void *fp);
};
