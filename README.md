# better-ls
a custom cli-interface that mimics 'ls -al', with some improvements  

## Intended structure  
better-ls/  
├── src/  
│   ├── main.c  
│   ├── args.c              # arg parsing  
│   ├── file.c              # single file ops  
│   ├── dir.c               # plan: single dir, recursion, filtering, etc  
│   ├── info.c              # metadata extraction (size, ext, modified time, etc.)  
│   ├── print.c             # output formatting  
│   └── utils.c             # helpers  
│  
├── include/  
│   ├── args.h  
│   ├── file.h  
│   ├── dir.h  
│   ├── info.h  
│   ├── print.h  
│   └── utils.h  
│  
├── Makefile  
