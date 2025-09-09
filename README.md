# better-ls
a custom cli-interface that mimics 'ls -al', with some improvements  

## Intended structure  
better-ls/  
├── src/  
│   ├── main.c  
│   ├── file.c              # single file ops  
│   ├── dir.c               # plan: single dir, recursion, filtering, etc  
│   ├── info.c              # metadata extraction (size, ext, modified time, etc.)  
│   ├── print.c             # output formatting  
│   └── utils.c             # helpers  
│  
├── include/  
│   ├── file.h  
│   ├── dir.h  
│   ├── info.h  
│   ├── print.h  
│   └── utils.h  
│  
├── Makefile  

## TODO
- option to skip/include hidden files  
- error checking non-existent files  

## Implementation plan
- if entry is a dir, populate only 'is_dir' variable, when printing, only print the "header", skip other metadata  
- make 'parent' as a var for a file entry, when printing horizontally, structurally divide each dir by a new line  

## Future
- structured spacing  
- more flags  
- wildcarding?  
