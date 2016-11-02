# helios

Jason Van Kerkhoven (100974276)
Brydon Gibson (100975274)

helios is an operating-system-to-be that even if it fails, will still be better than Solaris

Current implementation is a first-come-first-serve task scheduler. It uses linked lists to store PCB's in a wait set and a ready set, plus a PCB running in the processor (there should be one in the processor at almost all times). All PCB's should be found there, at least for the time being.

The current 'main' binary was built on a linux system. It is included because I'm too lazy to learn how gitignore works.
