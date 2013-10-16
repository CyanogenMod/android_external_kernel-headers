This directory contains the uapi version of original kernel headers that are
used to generate Bionic's "cleaned-up" user-land headers. The
architectural-independent ones (eg asm-generic, linux, ...) are retrieved
from the include/uapi directory in the kernel distribution. The
architectural-dependent ones are retrieved from the
arch/<arch_name>/include/uapi directory. There are also generated headers
(eg errno.h, posix_types.h, ...) by doing
"make ARCH=<arch_name> headers_install" in the kernel directory. The generated
headers can be found at "arch/<arch_name>/include/generated/asm" and they
should be copied over to the architectural-dependent directory.

They are mostly covered by the GPLv2 + exception, and thus cannot be distributed as part of the platform itself.
(NOTE: The cleaned up headers do not contain copyrightable information and are distributed with Bionic)

For more details, please read bionic/libc/kernel/README.TXT
