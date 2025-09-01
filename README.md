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

## Future
- structured spacing  
- more flags  
- wildcarding?  
