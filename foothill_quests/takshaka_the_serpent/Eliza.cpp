

#include "Eliza.h"

#include <bits/stdc++.h>

using namespace std;

string lispify(string s) {
  ostringstream result;
  for (const auto &c : s) {
    switch (c) {
      case 'S':
        result << "Th";
        break;

      case 's':
        result << "th";
        break;

      default:
        result << c;
    }
  }
  return result.str();
}

string rotate_vowels(string &s) {
  for (auto &c : s) {
    switch (c) {
      case 'A':
        c = 'E';
        break;

      case 'E':
        c = 'I';
        break;

      case 'I':
        c = 'O';
        break;

      case 'O':
        c = 'U';
        break;

      case 'U':
        c = 'A';
        break;

      case 'a':
        c = 'e';
        break;

      case 'e':
        c = 'i';
        break;

      case 'i':
        c = 'o';
        break;

      case 'o':
        c = 'u';
        break;

      case 'u':
        c = 'a';
        break;
    }
  }
  return s;
}

void enter() {
  cout << "What?\n";
  for (;;) {
    string input;
    getline(cin, input);

    if (input.empty()) {
      cout << "What?\n";
      continue;
    }

    cout << "    " << input << "\n\n";

    if (input.find('!') != string::npos) {
      cout << "OMG! You don't say!! " << input << "!!!!!\n";
      continue;
    }

    string uppercase_input(input);
    for (auto &c : uppercase_input) {
      c = toupper(c);
    }

    if (uppercase_input.find("WHY") != string::npos ||
        uppercase_input.find("WHAT") != string::npos) {
      cout << "I'm sorry, I don't like questions that contain what or why.\n";
      continue;
    }

    if (uppercase_input.find('S') != string::npos) {
      cout << "Interethting. When did you thtop thtopping your thibilanth?\n"
           << lispify(input) << "! Sheesh! Now what?\n";
      continue;
    }

    if (uppercase_input.find("BYE") != string::npos ||
        uppercase_input.find("QUIT") != string::npos) {
      cout << "Ok Bye. Nice being a force of change in your life.\n";
      break;
    }

    if (rand() % 10 < 8) {
      cout << rotate_vowels(input) << "?\n";
    } else {
      cout << "Huh? Why do you say: " << input << "?\n";
    }
  }
}
