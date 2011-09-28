This module blocks sendfile(2) to block the mbuf bug described in SA-10:07.mbuf


# Usage
env PATH=/bin:/sbin:/usr/sbin:/usr/bin /bin/sh -c "make clean && make && make load"
