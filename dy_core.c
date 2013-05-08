/* dy_core.c */

#include "jd_pretty.h"
#include "dynatron.h"
#include "utils.h"

static int clone_h(jd_var *self, jd_var *ctx, jd_var *arg) {
  scope {
    jd_var *name, *slot, *cfg;

    dy_debug("clone object, self=%lJ, ctx=%lJ, arg=%lJ", self, ctx, arg);

    if (name = jd_get_ks(arg, "name", 0), !name) {
      dy_listener_send_error("No name in %lJ", arg);
      JD_RETURN(0);
    }

    jd_var *super = jd_nv();
    dy_object_name(self, super);

    jd_var *proto = jd_nhv(1);
    slot = jd_get_ks(proto, "config", 1);
    if (cfg = jd_get_ks(arg, "config", 0), cfg)
      jd_assign(slot, cfg);
    else
      jd_set_hash(slot, 1);

    dy_debug("%V extends %V, prototype: %lJ", name, super, proto);

    dy_object_register(jd_bytes(name, NULL), proto, jd_bytes(super, NULL));
  }
  return 0;
}

static void despatch_message(jd_var *self, jd_var *msg) {
  jd_var *verb = jd_get_ks(msg, "verb", 0);
  if (!verb) {
    dy_listener_send_error("Message %lJ has no verb");
    return;
  }
  if (!dy_object_invokev(self, verb, msg)) {
    dy_debug("Message %J rejected", msg);
    /* TODO send to any downstream objects */
  }
}

static void describe(jd_var *self) {
  scope {
    jd_var *name = jd_nv(), *stash = jd_nv();
    dy_object_name(self, name);
    dy_object_stash(self, stash);
    dy_debug("name: %V, stash: %lJ", name, stash);
  }
}

static int run_h(jd_var *self, jd_var *ctx, jd_var *arg) {
  (void) ctx;
  (void) arg;
  describe(self);
  for (;;) scope {
    jd_var *msg = jd_nv();
    dy_object_get_message(self, msg);
    dy_debug("%J got message %lJ", self, msg);
    despatch_message(self, msg);
  }
  return 0;
}

void dy_core_init(void) {
  scope {
    jd_var *obj = jd_nhv(1);

    dy_object_set_method(obj, "clone", clone_h);
    dy_object_set_method(obj, "run", run_h);

    dy_object_register("core", obj, NULL);
  }
}

void dy_core_destroy(void) {
  dy_object_unregister("core");
}

/* vim:ts=2:sw=2:sts=2:et:ft=c
 */
