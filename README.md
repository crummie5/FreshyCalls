## FreshyCalls: Syscalls Freshly Squeezed!
> This library was made for **academic purposes only**. The authors are not responsible for what is given to this library and therefore we are exempt from any liability arising from the misuse of it.

**Uses C++17**
**x64 ONLY**

FreshyCalls tries to make the use of syscalls comfortable and simple, without generating too much boilerplate and in modern C++!
Doesn't it bother you to have to define every syscall stub or function within a module? Or having to depend on the Windows version for the syscalls? Well, forget about all that. FreshyCalls makes use of some features implemented from C++11 such as the variadic templates along with some custom mini-shellcode to avoid this.

This library is the product of having been playing around with syscalls for a few months. For example, the extraction of numbers was a fluke discovery while we were investigating how the syscalls worked. We saw that there was some sort of relationship between the number and the address of the stub. 
And the masked stub was just an idea after researching about InstrumentationCallback - great work by Ionescu, [more info here](https://github.com/ionescu007/HookingNirvana) - and seeing how ScyllaHide did it. 

We realized that they were [detecting manual syscalls by checking the return address](https://github.com/x64dbg/ScyllaHide/blob/master/HookLibrary/HookedFunctions.cpp#L176-L187) so we thought AV/EDR solutions might were doing the same hence we implemented it. Of course this can be "good" and "bad" at the same time, you avoid them to know that it is a manual syscall - at least with the InstrumentationCallback method - but you make it easier for them to detect which syscall is executed.

`CallSyscall`/`DirectCallSyscall` returns a struct that represents the result of the call, `FunctionResult`. This will facilitate error handling. Note that the rest of functions do internal error handlings and might generate exceptions. 
For instance, a piece of code from the PoC:
```cpp
syscall.CallSyscall("NtOpenProcessToken", HANDLE(-1), TOKEN_ADJUST_PRIVILEGES, &token_handle)
      .OrDie("[ActiveSeDebug] An error happened while opening the current process token: \"{{result_msg}}\" (Error Code: {{result_as_hex}})");
```

Be aware we have released this library "for fun" and it is by no means perfect. You should expect some bugs.

You can find an example of how to use it [here](https://github.com/Crummie5/Freshycalls_PoC) and a post explaining it a little more [here](https://www.crummie5.club/freshycalls/)