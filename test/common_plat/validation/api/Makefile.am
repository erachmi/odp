ODP_MODULES = atomic \
	      barrier \
	      buffer \
	      classification \
	      cpumask \
	      crypto \
	      errno \
	      hash \
	      init \
	      ipsec \
	      lock \
	      queue \
	      packet \
	      pktio \
	      pool \
	      random \
	      scheduler \
	      std_clib \
	      thread \
	      time \
	      timer \
	      traffic_mngr \
	      shmem \
	      system

SUBDIRS = $(ODP_MODULES)

#The tests will need to retain the deprecated test implementation
AM_CFLAGS += -Wno-deprecated-declarations
