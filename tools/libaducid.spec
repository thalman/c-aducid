Summary: ADUCID library
Name: libaducid
Version: @VERSION@
Release: @RELEASE@%{dist}
License: Apache License 2.0
Group: Applications/Libraries
Source: libaducid.tgz
BuildRoot: /var/tmp/%{name}-root
%{?el5:Requires: libcurl}
%{?el6:Requires: curl}
BuildRequires: make
BuildRequires: gcc
%{?el5:BuildRequires: curl-devel}
%{?el6:BuildRequires: libcurl-devel}
Provides: libaducid.so.2.50
Packager: Tomas Halman
%define pkgconfigdir %{_libdir}/pkgconfig

%description
ADUCID client library provides simplified usage of ADUCID infrastructure


%package devel
Summary: ADUCID development library
Group: Additional Development
%{?el5:BuildRequires: curl-devel}
%{?el6:BuildRequires: libcurl-devel}

%description devel
ADUCID client developement files

%prep
%setup -n libaducid

%build
# VER1 = 2.50
# VER2 = 0
VER1=`echo %{version} | cut -d . -f 1,2`
VER2=`echo %{version} | cut -d . -f 3`
VER3=%{version}

sed -r --in-place \
    -e "s/^MINORVERSION=.+$/MINORVERSION=$VER2/" \
    -e "s/MAJORVERSION=.+$/MAJORVERSION=$VER1/" \
    c/Makefile
make -C c clean
make -C c

%install
VER1=`echo %{version} | cut -d . -f 1,2`
VER2=`echo %{version} | cut -d . -f 3`
VER3=%{version}

/bin/rm -rf $RPM_BUILD_ROOT

install -d ${RPM_BUILD_ROOT}/%{_libdir}
install -d ${RPM_BUILD_ROOT}/%{_includedir}
install -d ${RPM_BUILD_ROOT}/%{pkgconfigdir}

strip --strip-unneeded c/libaducid.so.%{version}
install --mode 755 c/libaducid.so.%{version} ${RPM_BUILD_ROOT}/%{_libdir}
ln -s libaducid.so.$VER3 ${RPM_BUILD_ROOT}/%{_libdir}/libaducid.so.$VER1
ln -s libaducid.so.$VER3 ${RPM_BUILD_ROOT}/%{_libdir}/libaducid.so

install --mode 644 c/aducid.h ${RPM_BUILD_ROOT}/%{_includedir}/
sed -r -e "s#^prefix=.+#prefix=%{_prefix}#i" \
       -e "s#^exec_prefix=.+#exec_prefix=%{_prefix}#i" \
       -e "s#^libdir=.+#libdir=%{_libdir}#i" \
       -e "s#^includedir=.+#includedir=%{_includedir}#i" \
       -e "s#^Version:.+#Version: %{version}#i" \
misc/libaducid.pc >${RPM_BUILD_ROOT}/%{pkgconfigdir}/libaducid.pc

%clean
/bin/rm -rf $RPM_BUILD_ROOT

%files
%{_libdir}/libaducid.so.*

%files devel
%{pkgconfigdir}/libaducid.pc
%{_includedir}/aducid.h
%{_libdir}/libaducid.so
