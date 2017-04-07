# space-invaders

A terminal implementation of space invaders built in C with GNU ncurses.

## Error Handling

I tried to write in a highly modular way, with each function returning an error state. Based on this, processing in `main()` stops. Functions that indicate failure are always responsible for cleaning up after themselves (freeing memory, etc.).

