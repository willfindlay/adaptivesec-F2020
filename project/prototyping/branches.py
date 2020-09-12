import time

from bcc import BPF, PerfType, PerfHWConfig, PerfSWConfig

text = r"""

#include <uapi/linux/perf_event.h>

struct event {
    __u64 a;
    __u64 b;
    __u64 c;
};

BPF_STACK(stack, struct event, 10240);

int do_perf_event(struct bpf_perf_event_data *ctx)
{
    int written = 0;
    struct event entry = {};
    struct perf_branch_entry record = {};

    written = bpf_read_branch_records(ctx, &record, sizeof(record), 0);
    if (written <= 0) {
    bpf_trace_printk("error: %d\n", written);
        return 0;
    }

    stack.push(&entry, 0);

    return 0;
}

"""

b = BPF(text=text)
# Not working: problem -> need to use xattr to configure stack trace sampling
# (probably should just implement this in pybpf I guess)
b.attach_perf_event(ev_type=PerfType.HARDWARE, ev_config=PerfHWConfig.CPU_CYCLES, fn_name='do_perf_event', sample_freq=4000)

try:
    time.sleep(999999)
except KeyboardInterrupt:
    pass

while 1:
    try:
        print(b["stack"].pop().a)
    except KeyError:
        break
