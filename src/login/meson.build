#if 0 /// rename to elogind
# systemd_logind_sources = files('''
#         logind.c
#         logind.h
# '''.split())
#else
elogind_sources = files('''
        elogind.c
        elogind.h
        logind.c
        logind.h
'''.split())
#endif // 0

logind_gperf_c = custom_target(
        'logind_gperf.c',
        input : 'logind-gperf.gperf',
        output : 'logind-gperf.c',
        command : [gperf, '@INPUT@', '--output-file', '@OUTPUT@'])

#if 0 /// rename to elogind
# systemd_logind_sources += [logind_gperf_c]
#else
elogind_sources += [logind_gperf_c]
#endif // 0


liblogind_core_sources = files('''
        logind-core.c
        logind-device.c
        logind-device.h
        logind-button.c
        logind-button.h
        logind-action.c
        logind-action.h
        logind-seat.c
        logind-seat.h
        logind-session.c
        logind-session.h
        logind-session-device.c
        logind-session-device.h
        logind-user.c
        logind-user.h
        logind-inhibit.c
        logind-inhibit.h
        logind-dbus.c
        logind-session-dbus.c
        logind-seat-dbus.c
        logind-user-dbus.c
        logind-utmp.c
        logind-acl.h
'''.split())

#if 1 /// elogind has some additional files:
liblogind_core_sources += [files('''
        elogind-dbus.c
        elogind-dbus.h
'''.split()),
        libcore_la_sources,
        sleep_files,
        update_utmp_files]
#endif // 1
logind_acl_c = files('logind-acl.c')
if conf.get('HAVE_ACL', false)
        liblogind_core_sources += logind_acl_c
endif

liblogind_core = static_library(
        'logind-core',
        liblogind_core_sources,
        include_directories : includes,
#if 0 /// elogind needs audit support for utmp inclusion
#         dependencies : [libacl])
#else
        dependencies : [libacl,
                        libaudit])
#endif // 0

loginctl_sources = files('''
        loginctl.c
        sysfs-show.h
        sysfs-show.c
'''.split())

#if 1 /// elogind has some additional files:
loginctl_sources += files('''
        eloginctl.c
        eloginctl.h
'''.split())
#endif // 1
#if 0 /// elogind builds itself unconditionally and with some adaptatins
# if conf.get('ENABLE_LOGIND', false)
#         logind_conf = configure_file(
#                 input : 'logind.conf.in',
#                 output : 'logind.conf',
#                 configuration : substs)
#         install_data(logind_conf,
#                      install_dir : pkgsysconfdir)
#
#         pam_systemd_sym = 'src/login/pam_systemd.sym'
#         pam_systemd_c = files('pam_systemd.c')
#
#         install_data('org.freedesktop.login1.conf',
#                      install_dir : dbuspolicydir)
#         install_data('org.freedesktop.login1.service',
#                      install_dir : dbussystemservicedir)
#
#         custom_target(
#                 'org.freedesktop.login1.policy',
#                 input : 'org.freedesktop.login1.policy.in',
#                 output : 'org.freedesktop.login1.policy',
#                 command : intltool_command,
#                 install : install_polkit,
#                 install_dir : polkitpolicydir)
#
#         install_data('70-power-switch.rules',
#                      '70-uaccess.rules',
#                      install_dir : udevrulesdir)
#
#         foreach file : ['71-seat.rules',
#                         '73-seat-late.rules']
#                 gen = configure_file(
#                         input : file + '.in',
#                         output : file,
#                         configuration : substs)
#                 install_data(gen,
#                              install_dir : udevrulesdir)
#         endforeach
#
#         custom_target(
#                 'systemd-user',
#                 input : 'systemd-user.m4',
#                 output: 'systemd-user',
#                 command : [m4, '-P'] + m4_defines + ['@INPUT@'],
#                 capture : true,
#                 install : pamconfdir != 'no',
#                 install_dir : pamconfdir)
# endif
#else
logind_conf = configure_file(
        input : 'logind.conf.in',
        output : 'logind.conf',
        configuration : substs)
install_data(logind_conf,
                install_dir : pkgsysconfdir)

pam_elogind_sym = 'src/login/pam_elogind.sym'
pam_elogind_c = files('pam_elogind.c')

install_data('org.freedesktop.login1.conf',
                install_dir : dbuspolicydir)
install_data('org.freedesktop.login1.service',
                install_dir : dbussystemservicedir)

custom_target(
        'org.freedesktop.login1.policy',
        input : 'org.freedesktop.login1.policy.in',
        output : 'org.freedesktop.login1.policy',
        command : intltool_command,
        install : install_polkit,
        install_dir : polkitpolicydir)

install_data('70-power-switch.rules',
                '70-uaccess.rules',
                install_dir : udevrulesdir)

foreach file : ['71-seat.rules',
                '73-seat-late.rules']
        gen = configure_file(
                input : file + '.in',
                output : file,
                configuration : substs)
        install_data(gen,
                        install_dir : udevrulesdir)
endforeach

custom_target(
        'elogind-user',
        input : 'elogind-user.m4',
        output: 'elogind-user',
        command : [m4, '-P'] + m4_defines + ['@INPUT@'],
        capture : true,
        install : pamconfdir != 'no',
        install_dir : pamconfdir)
#endif //0
