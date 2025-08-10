-module(actor_supervisor).
-export([start/0, init/0]).

start() ->
    spawn(?MODULE, init, []).

init() ->
    process_flag(trap_exit, true),
    Worker1 = spawn_link(worker_actor, start, []),
    Worker2 = spawn_link(worker_actor, start, []),
    receive
        {'EXIT', Worker1, _Reason} ->
            io:format("Reiniciando Worker1~n"),
            spawn_link(worker, start, []);
        {'EXIT', Worker2, _Reason} ->
            io:format("Reiniciando Worker2~n"),
            spawn_link(worker, start, [])
    end.
