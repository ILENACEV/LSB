# LSB
This code is a steganography program that hides a message in an audio file by modifying the least significant bit (LSB) of the audio data. The message and the length of the message are hidden in the audio data. The output is a new audio file that has the same content as the original audio file, but with the added message. The message can later be extracted from the output audio file using the extract_text_from_audio function.

This code is for hiding a message within an audio file. The function hide_text_in_audio takes as input an audio file name (input_filename), a message to be hidden (message), and an output file name (output_filename). The function then performs the following operations:

Open the input audio file in binary mode.
Read the audio data from the file into a std::vector of chars.
Store the length of the message in the first few bits of the audio data.
Store the message in the following bits of the audio data.
Close the input audio file.
Open the output audio file in binary mode.
Write the audio data to the output audio file.
Close the output audio file.

The extract_text_from_audio function takes as input a file name and reads the audio data from the file, extracts the length and message stored in the audio data, and returns the message as a std::string.
