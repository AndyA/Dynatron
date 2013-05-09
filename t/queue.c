/* queue.t */

#include "framework.h"
#include "tap.h"
#include "jd_test.h"

#include "jd_pretty.h"
#include "dynatron.h"

static void test_queue(void) {
  scope {
    dy_queue *q;
    jd_var *msg = jd_nhv(1), *want = jd_nhv(1), *got = jd_nv();
    int i;

    q = dy_queue_new();

    for (i = 0; i < 5; i++) {
      jd_set_int(jd_get_ks(msg, "sn", 1), i);
      dy_queue_enqueue(q, msg);
    }

    is(dy_queue_available(q), 5, "5 items in queue");

    for (i = 0; i < 5; i++) {
      jd_set_int(jd_get_ks(want, "sn", 1), i);
      dy_queue_dequeue(q, got);
      jdt_is(got, want, "message %d", i);
    }

    is(dy_queue_available(q), 0, "0 items in queue");

    dy_queue_free(q);
  }
}

void test_main(void) {
  test_queue();
}

/* vim:ts=2:sw=2:sts=2:et:ft=c
 */
