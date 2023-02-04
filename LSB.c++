#include <iostream>
#include <fstream>
#include <vector>

const int BYTE_SIZE = 8;

void hide_text_in_audio(const char* input_filename, const std::string& message, const char* output_filename) {
    // Отворете ја влезната аудио датотека
    std::ifstream audio_file(input_filename, std::ios::binary);
    if (!audio_file.is_open()) {
        std::cerr << "Грешка: Не може да се отвори влезната аудио датотека " << input_filename << std::endl;
        return;
    }

    // Добијте ја должината на пораката
    int message_length = message.length();

    // Прочитајте ги аудио податоците од датотеката
    std::vector<char> audio_data((std::istreambuf_iterator<char>(audio_file)), std::istreambuf_iterator<char>());

    // Скриј ја должината на пораката во аудио податоците
    for (int i = 0; i < sizeof(int) * BYTE_SIZE; i++) {
        audio_data[i] = (audio_data[i] & ~1) | ((message_length >> i) & 1);
    }

    // Скриј ја пораката во аудио податоците
    int pos = sizeof(int) * BYTE_SIZE;
    for (const char& c : message) {
        for (int i = 0; i < BYTE_SIZE; i++) {
            audio_data[pos++] = (audio_data[pos] & ~1) | ((c >> i) & 1);
        }
    }

    // Затворете ја влезната аудио датотека
    audio_file.close();

    // Отворете ја излезната аудио датотека
    std::ofstream output_file(output_filename, std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Грешка: Не може да се отвори излезна аудио датотека " << output_filename << std::endl;
        return;
    }

    // Напишете ги аудио податоците во излезната датотека
    output_file.write(audio_data.data(), audio_data.size());

    // Затворете ја излезната аудио датотека
    output_file.close();
}

std::string extract_text_from_audio(const char *filename) {
  std::ifstream audio_file(filename, std::ios::binary);
  if (!audio_file.is_open()) {
    std::cerr << "Грешка: не успеа да се отвори аудио датотеката" << std::endl;
    return "";
  }

  // Читајте ги аудио податоците во вектор од бајти
  std::vector<char> audio_data((std::istreambuf_iterator<char>(audio_file)), std::istreambuf_iterator<char>());

  // Извлечете ја должината на пораката од првите 4 бајти од аудио податоците
  int message_length = 0;
  for (int i = 0; i < sizeof(int) * BYTE_SIZE; i++) {
    message_length |= (audio_data[i] & 1) << i;
  }

  // Извлечете ја пораката од преостанатите бајти на аудио податоците
  std::string message;
  int pos = sizeof(int) * BYTE_SIZE;
  for (int i = 0; i < message_length; i++) {
    char c = 0;
    for (int j = 0; j < BYTE_SIZE; j++) {
      c |= (audio_data[pos++] & 1) << j;
    }
    message.push_back(c);
  }

  // Затворете ја аудио датотеката
  audio_file.close();

  return message;
}

int main() {
 // Изберете дали да се скрие или извлече текст од аудио
 std::cout << "Внесете 1 за да го скриете текстот во аудио, 2 за да извлечете текст од аудио:";
 int choice;
 std::cin >> choice;

 switch (choice) {
    case 1: {
      // Скриј текст во аудио
      char input_filename[100];
      std::cout << "Внесете го името на влезната аудио датотека: ";
      std::cin >> input_filename;

      std::string message;
      std::cout << "Внесете ја пораката за да се скрие: ";
      std::cin.ignore();
      std::getline(std::cin, message);

      char output_filename[100];
      std::cout << "Внесете го името на излезната аудио датотека: ";
      std::cin >> output_filename;

      hide_text_in_audio(input_filename, message, output_filename);
      break;
    }
    case 2: {
      // Извадете текст од аудио
      char filename[100];
      std::cout << "Внесете го името на аудио датотеката: ";
      std::cin >> filename;

      std::string message = extract_text_from_audio(filename);
      std::cout << "Извлечена порака: " << message << std::endl;
      break;
    }
    default:
      std::cerr << "Грешка: неважечки избор" << std::endl;
      break;
  }

 return 0;
}
