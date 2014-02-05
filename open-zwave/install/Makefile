#!/usr/bin/make -f

OPENZWAVE = ../

all:
	$(MAKE) -j4 -C $(OPENZWAVE)cpp/build/linux

clean:
	$(MAKE) -C $(OPENZWAVE)cpp/build/linux clean

install:
	install -d $(DESTDIR)/etc/openzwave
	install -d $(DESTDIR)/usr/local/include
	install -d $(DESTDIR)/usr/local/include/openzwave
	install -d $(DESTDIR)/usr/local/share/openzwave
	install -d $(DESTDIR)/usr/local/lib
	cp -r $(OPENZWAVE)config $(DESTDIR)/usr/local/share/openzwave
	install $(OPENZWAVE)cpp/lib/linux/libopenzwave.so $(DESTDIR)/usr/local/lib
	install $(OPENZWAVE)cpp/lib/linux/libopenzwave.a $(DESTDIR)/usr/local/lib
	cp -r $(OPENZWAVE)cpp/src/*.h $(DESTDIR)/usr/local/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/value_classes/*.h $(DESTDIR)/usr/local/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/command_classes/*.h $(DESTDIR)/usr/local/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/platform/*.h $(DESTDIR)/usr/local/include/openzwave
	cp -r $(OPENZWAVE)cpp/src/platform/unix/*.h $(DESTDIR)/usr/local/include/openzwave
