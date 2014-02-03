#!/usr/bin/make -f

OPENZWAVE = ../

all:
	$(MAKE) -j4 -C $(OPENZWAVE)cpp/build/linux

clean:
	$(MAKE) -C $(OPENZWAVE)cpp/build/linux clean

install:
	install -d $(DESTDIR)/etc/openzwave
	install -d $(DESTDIR)/usr/include/openzwave
	install -d $(DESTDIR)/usr/share/openzwave
	install -d $(DESTDIR)/usr/lib
	cp -r $(OPENZWAVE)config $(DESTDIR)/usr/share/openzwave
	install $(OPENZWAVE)cpp/lib/linux/libopenzwave.so $(DESTDIR)/usr/lib
	install $(OPENZWAVE)cpp/lib/linux/libopenzwave.a $(DESTDIR)/usr/lib
	cp -r $(OPENZWAVE)cpp/src/*.h $(DESTDIR)/usr/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/value_classes/*.h $(DESTDIR)/usr/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/command_classes/*.h $(DESTDIR)/usr/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/platform/*.h $(DESTDIR)/usr/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/platform/unix/*.h $(DESTDIR)/usr/include/openzwave
