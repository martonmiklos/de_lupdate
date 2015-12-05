# de_lupdate
Push localized strings from *.ts files back to the source

This tool can be used to change your Qt codebase to a localization translated to a *.ts file.

This tool can be helpful in the following cases:
- You have started the development in English for e.g. while all of your users are using your software localized. 
Translating the strings after each release it time consuming, so you would like to pull back all localized strings from
the ts file to your codebase. 

Known limitations:
- The ts file must be generated/updated  with lupdate -locations relative to transfer the line numbers to the ts file.
- In the C++ code you can have multiline strings. Do not leave more than one row between the ts( (or whatever macro are you using) 
and the start of your strings.
