#include "scanner.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::vector;

bool isID(const std::string &str) {
  if (str == "main")
    return false;
  if (std::isdigit(str[0]))
    return false;
  int counter = 0;
  if (str[0] == '_')
    counter++;

  for (; counter < str.size(); counter++)
    if (!(isalnum(str[counter])))
      return false;

  return true;
}
bool isComment(const std::string &str) { return str == "/*" || str == "//"; }

bool isDigit(const std::string &str) {
  return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isString(const std::string &str) {
  return str[0] == '"' && str[str.size() - 1] == '"';
}

bool isChar(const std::string &str) { return str[0] == '\'' && str[2] == '\''; }
bool isBool(const std::string &str) { return str == "true" || str == "false"; }

bool isLiteral(const std::string &str) {
  return isDigit(str) || isString(str) || isChar(str) || isBool(str);
}

bool isKeyword(const std::string &str) {
  const vector<std::string> keywords{"int",  "float",  "char",
                                     "auto", "double", "do",
                                     "main", "switch", "return"};
  for (const auto &keyword : keywords)
    if (keyword == str)
      return true;

  return false;
}

bool isStatement(const std::string &str) {
  const vector<std::string> statements{"for", "while"};
  for (const auto &statement : statements)
    if (statement == str)
      return true;

  return false;
}

bool isOperator(const std::string &str) {
  const vector<std::string> operators{
      "<", ">",  "<=", ">=", "*",  "+",  "-",  "/",
      "=", "-=", "*=", "+=", "/=", "++", "--", "=="};
  for (const auto &op : operators)
    if (op == str)
      return true;

  return false;
}

bool isSeparator(const std::string &str) {
  const vector<std::string> Separators{"{", "}", ",", "(", ")", ";"};
  for (const auto &separate : Separators)
    if (separate == str)
      return true;

  return false;
}

bool isNoSpaces(const std::string &str) { return str == " " || str == "\n"; }

void printRoleOfToken(const std::string &token) {
  if (isOperator(token))
    cout << "(operator, " << token << ")\n";
  else if (isSeparator(token))
    cout << "(separator, " << token << ")\n";
  else if (isKeyword(token))
    cout << "(keyword, " << token << ")\n";
  else if (isStatement(token))
    cout << "(statement, " << token << ")\n";
  else if (isLiteral(token))
    cout << "(literal, " << token << ")\n";
  else if (isID(token))
    cout << "(identifier, " << token << ")\n";
  else if (isComment(token))
    cout << "(comment, " << token << ")\n";
  else
    throw std::runtime_error("Invalid token: " + token + "\n");
}

void lexicalAnalyze(const std::string &nameOfFile) {
  char ch;
  std::string buffer;
  std::fstream file(nameOfFile, std::fstream::in);

  if (!file.is_open()) {
    cout << "error while opening the file\n";
    exit(0);
  }

  bool miltiCm = false, singleCm = false;
  while (file >> std::noskipws >> ch) {
    if (singleCm || miltiCm) {
      if (singleCm && ch == '\n')
        singleCm = false;

      if (miltiCm && ch == '*') {
        if (!(file >> ch)) {
          std::cerr << "Error: multi-line comment not closed before EOF!\n";
          break;
        }

        if (ch == '/')
          miltiCm = false;
      }
      continue;
    }

    if (ch == '/') {
      std::string comm(1, ch);
      file >> ch;
      if (ch == EOF) {
        printRoleOfToken(comm);
        break;
      }

      if (ch == '*') {
        miltiCm = true;
        comm += ch;
      } else if (ch == '/') {
        singleCm = true;
        comm += ch;
      }
      if (miltiCm || singleCm) {
        printRoleOfToken(comm);
        continue;
      }
    }

    if (isNoSpaces(std::string(1, ch))) {
      if (!buffer.empty()) {
        printRoleOfToken(buffer);
        buffer = "";
      }
      continue;
    }

    if (isOperator(std::string(1, ch)) && !isOperator(buffer)) {
      if (!buffer.empty()) {
        printRoleOfToken(buffer);
        buffer = "";
      }
    }

    if (!isOperator(std::string(1, ch)) && isOperator(buffer)) {
      printRoleOfToken(buffer);
      buffer = "";
    }

    if (isSeparator(std::string(1, ch))) {
      if (!buffer.empty()) {
        printRoleOfToken(buffer);
        buffer = "";
      }
      if (isSeparator(std::string(1, ch))) {
        printRoleOfToken(std::string(1, ch));
        continue;
      }
    }
    buffer += ch;
  }
  file.close();
}
