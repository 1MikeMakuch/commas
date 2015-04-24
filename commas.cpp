// commas
// Mike Makuch 2013
// reads text from stdin and emits it on stdout inserting commas into numbers for readability
/* usage:

	$ ls -l testdatafile.1000M 
	-rw-rw-r--+ 1 mkm  wheel  1048576000 Apr 24 12:45 testdatafile.1000M

	$ ls -l testdatafile.1000M  | commas
	-rw-rw-r--+ 1 mkm  wheel  1,048,576,000 Apr 24 12:45 testdatafile.1000M
*/

#include <iostream>
#include <string>
using namespace std;

void doword(const bool isnum, const string & word) {
  if (!word.length())
    return;
  if (!isnum) {
    cout << word;
    return;
  }
  // asdf, 123
  string cword;
  for(int i=0,j=word.length()-1 ; i < word.length(); --j,i++) {
    char ch = word[i];
    cword.append(1,ch);
    if (j && j % 3 == 0)
      cword.append(1,',');
  }
  cout << cword;


}
void doline(const string & line) {
  int pos {0};
  string word;
  bool isnum = false;
  while(pos < line.length()) {
    char ch = line[pos++];
    if (' ' == ch || '\t' == ch) {
      doword(isnum,word); word="";
      cout << ch;
    } else {
      if (word.length() == 0) {
        if ('-' == ch || ('0' <= ch && ch <= '9')) {
          isnum = true;
        } else 
          isnum = false;
      } else if (isnum && !('0' <= ch && ch <= '9')) {
        isnum = false;
      }
      word.append(1,ch);
    }
  }
  if (word.length()) {
    doword(isnum,word);
    //				cout << endl;
  }
}

int main(int argc, char * argv[]) {
  string line;
  if (argc>1) {
    line = argv[1];
    doline(line);
  } else {
    while(getline(cin, line)) {
      doline(line);
      cout << endl;
    }
  }
}

