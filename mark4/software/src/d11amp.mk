d11amp_MODULES:=	audiooutput/audiooutput \
			audiooutput/audiooutput_portaudio \
			decoder/decoder \
			decoder/decoder_mp3 \
			gui/default_theme \
			gui/gui_helpers \
			gui/gui_top \
			gui/theme_elements \
			gui/theme_manager \
			gui/visualizer \
			gui/window_equalizer \
			gui/window_license \
			gui/window_main \
			gui/window_playlist \
			main/controller \
			main/main \
			main/print_screens \
			playlist/playlist \
			shared/config \
			shared/license
d11amp_INCLUDES:=	-Isrc/audiooutput \
			-Isrc/decoder \
			-Isrc/gui \
			-Isrc/main \
			-Isrc/playlist \
			-Isrc/shared
d11amp_LDFLAGS:=	-Wl,--as-needed
d11amp_LIBS:=		m
d11amp_PKGDEPS:=	gdk-pixbuf-2.0 gtk4 libmpg123 portaudio-2.0 libzip

$(call binrules, d11amp)

MAN1DIR?=	$(prefix)/share/man1
install::
	mkdir -p $(DESTDIR)$(MAN1DIR)
	cp d11amp.1 $(DESTDIR)$(MAN1DIR)
