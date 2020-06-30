int VLstore(char *name, char *val);
char *VLlookup(char *name);
void VLlist();
int VLexport(char *name);
int VLenviron2table(char *env[]);
char **VLtable2environ();