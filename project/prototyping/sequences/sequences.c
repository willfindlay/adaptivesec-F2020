#include "sequences.h"

BPF_ARRAY(_sequence_init, struct sequence_t, 1);
BPF_HASH(sequences, u32, struct sequence_t, 10240);
BPF_TABLE("lru_hash", struct sequence_t, u64, sequence_counts, 10240 << 1);

static __always_inline int do_lsm_common(enum lsm_id_t id, u32 pid)
{
    int zero = 0;
    struct sequence_t *s;

    s = _sequence_init.lookup(&zero);
    if (!s)
        return 0;

    s = sequences.lookup_or_try_init(&pid, s);
    if (!s)
        return 0;

    for (u16 i = SEQUENCE_LENGTH - 1; i > 0; i--) {
        s->value[i] = s->value[i - 1];
    }
    s->value[0] = (u16)id;

    u64 count_init = 0;
    u64 *count = sequence_counts.lookup_or_try_init(s, &count_init);
    if (!count)
        return 0;
    lock_xadd(count, 1);

    return 0;
}

LSM_PROBE(bprm_check_security, struct linux_binprm *bprm)
{
    return do_lsm_common(LSM_BPRM_CHECK_SECURITY, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_alloc, struct task_struct *task, unsigned long clone_flags)
{
    struct task_struct *c = task;
    struct task_struct *p = task->parent;

    do_lsm_common(LSM_TASK_ALLOC, c->pid);
    do_lsm_common(LSM_TASK_ALLOC, p->pid);

    return 0;
}

LSM_PROBE(task_free, struct task_struct *task)
{
    u32 pid = task->pid;

    do_lsm_common(LSM_TASK_FREE, pid);
    sequences.delete(&pid);

    return 0;
}

LSM_PROBE(task_setpgid, int unused)
{
    return do_lsm_common(LSM_TASK_SETPGID, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_getpgid, int unused)
{
    return do_lsm_common(LSM_TASK_GETPGID, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_getsid, int unused)
{
    return do_lsm_common(LSM_TASK_GETSID, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_setnice, int unused)
{
    return do_lsm_common(LSM_TASK_SETNICE, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_setioprio, int unused)
{
    return do_lsm_common(LSM_TASK_SETIOPRIO, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_getioprio, int unused)
{
    return do_lsm_common(LSM_TASK_GETIOPRIO, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_prlimit, int unused)
{
    return do_lsm_common(LSM_TASK_PRLIMIT, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_setrlimit, int unused)
{
    return do_lsm_common(LSM_TASK_SETRLIMIT, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_setscheduler, int unused)
{
    // TODO probably need to treat this as a special case
    // to reduce non-determinism
    return do_lsm_common(LSM_TASK_SETSCHEDULER, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_getscheduler, int unused)
{
    // TODO probably need to treat this as a special case
    // to reduce non-determinism
    return do_lsm_common(LSM_TASK_GETSCHEDULER, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_movememory, int unused)
{
    return do_lsm_common(LSM_TASK_MOVEMEMORY, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_kill, int unused)
{
    return do_lsm_common(LSM_TASK_KILL, bpf_get_current_pid_tgid());
}

LSM_PROBE(task_prctl, int unused)
{
    return do_lsm_common(LSM_TASK_PRCTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(sb_statfs, int unused)
{
    return do_lsm_common(LSM_SB_STATFS, bpf_get_current_pid_tgid());
}

LSM_PROBE(sb_mount, int unused)
{
    return do_lsm_common(LSM_SB_MOUNT, bpf_get_current_pid_tgid());
}

LSM_PROBE(sb_remount, int unused)
{
    return do_lsm_common(LSM_SB_REMOUNT, bpf_get_current_pid_tgid());
}

LSM_PROBE(sb_umount, int unused)
{
    return do_lsm_common(LSM_SB_UMOUNT, bpf_get_current_pid_tgid());
}

LSM_PROBE(sb_pivotroot, int unused)
{
    return do_lsm_common(LSM_SB_PIVOTROOT, bpf_get_current_pid_tgid());
}

LSM_PROBE(move_mount, int unused)
{
    return do_lsm_common(LSM_MOVE_MOUNT, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_create, int unused)
{
    return do_lsm_common(LSM_INODE_CREATE, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_link, int unused)
{
    return do_lsm_common(LSM_INODE_LINK, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_symlink, int unused)
{
    return do_lsm_common(LSM_INODE_SYMLINK, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_mkdir, int unused)
{
    return do_lsm_common(LSM_INODE_MKDIR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_rmdir, int unused)
{
    return do_lsm_common(LSM_INODE_RMDIR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_mknod, int unused)
{
    return do_lsm_common(LSM_INODE_MKNOD, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_rename, int unused)
{
    return do_lsm_common(LSM_INODE_RENAME, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_readlink, int unused)
{
    return do_lsm_common(LSM_INODE_READLINK, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_follow_link, int unused)
{
    return do_lsm_common(LSM_INODE_FOLLOW_LINK, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_permission, int unused)
{
    // TODO: split this into READ, WRITE, APPEND, EXEC
    return do_lsm_common(LSM_INODE_PERMISSION, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_setattr, int unused)
{
    return do_lsm_common(LSM_INODE_SETATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_getattr, int unused)
{
    return do_lsm_common(LSM_INODE_GETATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_setxattr, int unused)
{
    return do_lsm_common(LSM_INODE_SETXATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_getxattr, int unused)
{
    return do_lsm_common(LSM_INODE_GETXATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_listxattr, int unused)
{
    return do_lsm_common(LSM_INODE_LISTXATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(inode_removexattr, int unused)
{
    return do_lsm_common(LSM_INODE_REMOVEXATTR, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_permission, int unused)
{
    // TODO: split this into READ, WRITE, APPEND, EXEC
    return do_lsm_common(LSM_FILE_PERMISSION, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_ioctl, int unused)
{
    return do_lsm_common(LSM_FILE_IOCTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(mmap_addr, int unused)
{
    return do_lsm_common(LSM_MMAP_ADDR, bpf_get_current_pid_tgid());
}

LSM_PROBE(mmap_file, int unused)
{
    return do_lsm_common(LSM_MMAP_FILE, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_mprotect, int unused)
{
    return do_lsm_common(LSM_FILE_MPROTECT, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_lock, int unused)
{
    return do_lsm_common(LSM_FILE_LOCK, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_fcntl, int unused)
{
    return do_lsm_common(LSM_FILE_FCNTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_send_sigiotask, int unused)
{
    return do_lsm_common(LSM_FILE_SEND_SIGIOTASK, bpf_get_current_pid_tgid());
}

LSM_PROBE(file_receive, int unused)
{
    return do_lsm_common(LSM_FILE_RECEIVE, bpf_get_current_pid_tgid());
}

LSM_PROBE(unix_stream_connect, int unused)
{
    // TODO consider moving this to a common socket id
    return do_lsm_common(LSM_UNIX_STREAM_CONNECT, bpf_get_current_pid_tgid());
}

LSM_PROBE(unix_may_send, int unused)
{
    // TODO consider moving this to a common socket id
    return do_lsm_common(LSM_UNIX_MAY_SEND, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_create, int unused)
{
    return do_lsm_common(LSM_SOCKET_CREATE, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_socketpair, int unused)
{
    return do_lsm_common(LSM_SOCKET_SOCKETPAIR, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_bind, int unused)
{
    return do_lsm_common(LSM_SOCKET_BIND, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_connect, int unused)
{
    return do_lsm_common(LSM_SOCKET_CONNECT, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_listen, int unused)
{
    return do_lsm_common(LSM_SOCKET_LISTEN, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_accept, int unused)
{
    return do_lsm_common(LSM_SOCKET_ACCEPT, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_sendmsg, int unused)
{
    return do_lsm_common(LSM_SOCKET_SENDMSG, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_recvmsg, int unused)
{
    return do_lsm_common(LSM_SOCKET_RECVMSG, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_getsockname, int unused)
{
    return do_lsm_common(LSM_SOCKET_GETSOCKNAME, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_getpeername, int unused)
{
    return do_lsm_common(LSM_SOCKET_GETPEERNAME, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_getsockopt, int unused)
{
    return do_lsm_common(LSM_SOCKET_GETSOCKOPT, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_setsockopt, int unused)
{
    return do_lsm_common(LSM_SOCKET_SETSOCKOPT, bpf_get_current_pid_tgid());
}

LSM_PROBE(socket_shutdown, int unused)
{
    return do_lsm_common(LSM_SOCKET_SHUTDOWN, bpf_get_current_pid_tgid());
}

LSM_PROBE(tun_dev_create, int unused)
{
    return do_lsm_common(LSM_TUN_DEV_CREATE, bpf_get_current_pid_tgid());
}

LSM_PROBE(tun_dev_attach, int unused)
{
    return do_lsm_common(LSM_TUN_DEV_ATTACH, bpf_get_current_pid_tgid());
}

LSM_PROBE(key_alloc, int unused)
{
    return do_lsm_common(LSM_KEY_ALLOC, bpf_get_current_pid_tgid());
}

LSM_PROBE(key_free, int unused)
{
    return do_lsm_common(LSM_KEY_FREE, bpf_get_current_pid_tgid());
}

LSM_PROBE(key_permission, int unused)
{
    return do_lsm_common(LSM_KEY_PERMISSION, bpf_get_current_pid_tgid());
}

LSM_PROBE(ipc_permission, int unused)
{
    return do_lsm_common(LSM_IPC_PERMISSION, bpf_get_current_pid_tgid());
}

LSM_PROBE(msg_queue_associate, int unused)
{
    return do_lsm_common(LSM_MSG_QUEUE_ASSOCIATE, bpf_get_current_pid_tgid());
}

LSM_PROBE(msg_queue_msgctl, int unused)
{
    return do_lsm_common(LSM_MSG_QUEUE_MSGCTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(msg_queue_msgsnd, int unused)
{
    return do_lsm_common(LSM_MSG_QUEUE_MSGSND, bpf_get_current_pid_tgid());
}

LSM_PROBE(shm_associate, int unused)
{
    return do_lsm_common(LSM_SHM_ASSOCIATE, bpf_get_current_pid_tgid());
}

LSM_PROBE(shm_shmctl, int unused)
{
    return do_lsm_common(LSM_SHM_SHMCTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(shm_shmat, int unused)
{
    return do_lsm_common(LSM_SHM_SHMAT, bpf_get_current_pid_tgid());
}

/* TODO: maybe add hooks for system V semaphores... need to check if this can
 * cause a deadlock with our runtime allocated maps */

/* TODO: maybe add binder hooks here */

LSM_PROBE(ptrace_access_check, int unused)
{
    return do_lsm_common(LSM_PTRACE_ACCESS_CHECK, bpf_get_current_pid_tgid());
}

LSM_PROBE(ptrace_traceme, int unused)
{
    return do_lsm_common(LSM_PTRACE_TRACEME, bpf_get_current_pid_tgid());
}

LSM_PROBE(capget, int unused)
{
    // TODO: maybe split this by capabilities
    return do_lsm_common(LSM_CAPGET, bpf_get_current_pid_tgid());
}

LSM_PROBE(capset, int unused)
{
    // TODO: maybe split this by capabilities
    return do_lsm_common(LSM_CAPSET, bpf_get_current_pid_tgid());
}

LSM_PROBE(capable, int unused)
{
    // TODO: maybe split this by capabilities
    return do_lsm_common(LSM_CAPABLE, bpf_get_current_pid_tgid());
}

LSM_PROBE(quotactl, int unused)
{
    return do_lsm_common(LSM_QUOTACTL, bpf_get_current_pid_tgid());
}

LSM_PROBE(quota_on, int unused)
{
    return do_lsm_common(LSM_QUOTA_ON, bpf_get_current_pid_tgid());
}

LSM_PROBE(syslog, int unused)
{
    return do_lsm_common(LSM_SYSLOG, bpf_get_current_pid_tgid());
}

LSM_PROBE(settime, int unused)
{
    return do_lsm_common(LSM_SETTIME, bpf_get_current_pid_tgid());
}

LSM_PROBE(vm_enough_memory, int unused)
{
    return do_lsm_common(LSM_VM_ENOUGH_MEMORY, bpf_get_current_pid_tgid());
}

LSM_PROBE(bpf, int unused)
{
    return do_lsm_common(LSM_BPF, bpf_get_current_pid_tgid());
}

LSM_PROBE(bpf_map, int unused)
{
    return do_lsm_common(LSM_BPF_MAP, bpf_get_current_pid_tgid());
}

LSM_PROBE(bpf_prog, int unused)
{
    return do_lsm_common(LSM_BPF_PROG, bpf_get_current_pid_tgid());
}

LSM_PROBE(perf_event_open, int unused)
{
    return do_lsm_common(LSM_PERF_EVENT_OPEN, bpf_get_current_pid_tgid());
}
