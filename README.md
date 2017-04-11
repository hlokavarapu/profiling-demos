Profiling Demos
===============

This is a collection of demos on how to do generate performance captures
(profiling) of c++ code.


- 
deal.II TimerOutput

   MPI_Barrier  
   start timing

   your code

   mpi_Barrier
   stop()

 
///
  Timer timer;

  timer.start();

  // do something

  timer.stop();
  double time = timer();
  MinMaxAvg data = Utilities::MPI::min_max_avg(time, MPI_COMM_WORLD);
  data.min, data.max

2. g++ profiling
   - compile with -g
   - run
   - visualize with kcachegrind
   not parallel

3. valgrind with tool kcachegrind
   not parallel
   
deal.II TimerOutput / Timer
---------------------------

  - defined section
  - see ``step-40/``:
    ```
	{
            TimerOutput::Scope t(computing_timer, "setup");
	    // do something.
	}
    ```
  - will contain two MPI_Barriers to compute the maximum time
  - manual computation example: see ``MinMaxAvg`` in ``step-40/``

Simple mpi command profiling
----------------------------

  - see http://ipm-hpc.sourceforge.net/
  - examples: http://ipm-hpc.sourceforge.net/images/mpi_stack_byrank_16k.png
  - simple to install and use
  - only MPI statistics and from sections created manually
  - can link to PAPI for performance counters
  - create sections: 
    ```
        MPI_Pcontrol(1,"setup_amg");
        preconditioner.initialize(system_matrix, data);
        MPI_Pcontrol(-1,"setup_amg");
    ```
  - example: ``step-40/``:
    - ``LD_PRELOAD=/ssd/apps/IPM/installed/lib/libipm.so mpirun -n 4 ./step-40``
    - ``/ssd/apps/IPM/installed/bin/ipm_parse -html heister.<bla>.xml``
    - ``open <bla>/index.html``


Parallel tracing with hpc-toolkit
---------------------------------
   - Needs compiler wrappers
   - hard to setup
   - parallel traces of every function call for each processor
   - has overhead
   - examples: https://wiki.mpich.org/mpich/images/f/ff/HpctkAMRTrace.png



Parallel Trace Event Logging
----------------------------
   
  see ``trace-events/``
  - use event log to generate events
  - concat files using ``python plot.py event.json.* >out.json
  - visualize in chrome/chromium chrome://tracing







Timo Heister, timo.heister@gmail.com