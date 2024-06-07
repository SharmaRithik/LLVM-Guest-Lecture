; Optimized LLVM IR (example_opt.ll)
define i32 @main() #0 {
  %sum = alloca i32, align 4
  %constant1 = alloca i32, align 4
  %constant2 = alloca i32, align 4
  store i32 0, i32* %sum, align 4
  store i32 42, i32* %constant1, align 4
  store i32 24, i32* %constant2, align 4
  %0 = load i32, i32* %constant1, align 4
  %1 = load i32, i32* %constant2, align 4
  %mul = mul nsw i32 %0, %1
  %mul1 = mul nsw i32 %mul, 10000
  store i32 %mul1, i32* %sum, align 4
  %2 = load i32, i32* %sum, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i64 0, i64 0), i32 %2)
  ret i32 0
}
