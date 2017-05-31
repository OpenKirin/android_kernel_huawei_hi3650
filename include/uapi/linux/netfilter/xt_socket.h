#ifndef _XT_SOCKET_H
#define _XT_SOCKET_H

#include <linux/types.h>

enum {
	XT_SOCKET_TRANSPARENT = 1 << 0,
	XT_SOCKET_NOWILDCARD = 1 << 1,
};

struct xt_socket_mtinfo1 {
	__u8 flags;
};
#define XT_SOCKET_FLAGS_V1 XT_SOCKET_TRANSPARENT

struct xt_socket_mtinfo2 {
	__u8 flags;
};
#define XT_SOCKET_FLAGS_V2 (XT_SOCKET_TRANSPARENT | XT_SOCKET_NOWILDCARD)

struct sock *xt_socket_lookup_slow_v4(const struct sk_buff *skb,
				const struct net_device *indev);
struct sock *xt_socket_lookup_slow_v6(const struct sk_buff *skb,
				const struct net_device *indev);

#endif /* _XT_SOCKET_H */
