# HCA decoder

# How to decode HCA file

  Drag and drop a HCA file to HCADecoder.exe, you can create a WAVE file with the same file name.
  
  It supports decoding of multiple files.
  The decode option remains at the default value.


  *Specifying decoding options*
  
  Drag and drop a HCA file to the option specification Batch_Decode.bat.
  
  The batch file also supports decode of multiple files.


# Decryption method of HCA file

  Drag and drop a HCA file to Decode.bat, and the HCA file will be decrypted.
  
  **Please be careful as the original files will be overwritten.**
  
  The batch file supports decryption of multiple files.


# Specification

 The default decode option is:
  
  * Volume = 1 (times)
  
  * Bit mode = 16 (bits)
  
  * Loop count = 0 (times)
  
  * Decryption key = CC55463930DBE1AB *Key used in PSO2

  If loop information is included in the HCA file, a smpl chunk is added to the WAVE file.
  However, when the number of loops of the decode option is 1 or more, output as direct waveform data without adding the smpl chunk.
  The waveform data output at this time is as follows.
  * When there is no loop information in the HCA file, treat the loop start position and loop end position as the start position and end position respectively.
  [Start Position to Loop End Position] + [Loop Start Position ~ Loop End Position] × (Loop Count -1) + [Loop Start Position - End Position]

  If comment information is included in the HCA file, note chunk is added to the WAVE file.


# Notes

  Version check disabled.
  Decoding may fail if HCA after v2.1 comes out from now on.

  The damage check of the HCA header is also disabled.
  This is to make it easy to modify the header.
  Even if the header is really corrupt it will not result in an error.

  The key used in the encryption table varies depending on the game. *Some developer companies may use the same key.*
  
  When the type of the encryption table is 0x38 (Keyed Encryption), and you don't use the correct key, the output waveform will be incorrect.

  Decrypting with decryption key specified
  
  Open the batch file Batch_Decode.bat with a text editor and change the decryption key of the default value setting.

  It corresponds to CBR only. VBR fails to decode. *There is a chance that VBR does not exist.

  In the command prompt, the file path (file name and folder name) including & is
  When dragging and dropping it to a batch file such as option specification Decode.bat
  The file can not be opened and an error appears.


# Disclaimer

  The author does not take any responsibility for any damage caused by using this application.
  Please use it on your own responsibility.


# Other

  Since there is a trace of that VBR is removed from HCA v2.0, maybe only CBR exists from the beginning.

  There was a trace that ATH table also existed only in Type 0 (Keyless Encryption).

  Decoding normally will produce 16 bit PCM Wave files, so the sound quality will degrade!
  With option-specified decoding, setting bit mode to float will not degrade.
  However, since HCA itself is a lossy compression, it is originally degraded.
