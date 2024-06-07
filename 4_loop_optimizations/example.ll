; Original LLVM IR (example.ll)
define i32 @main() #0 {
  %sum = alloca i32, align 4
  %constant1 = alloca i32, align 4
  %constant2 = alloca i32, align 4
  store i32 0, i32* %sum, align 4
  store i32 42, i32* %constant1, align 4
  store i32 24, i32* %constant2, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %0
  %i = phi i32 [ 0, %0 ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i, 10000
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %0 = load i32, i32* %constant1, align 4
  %1 = load i32, i32* %constant2, align 4
  %mul = mul nsw i32 %0, %1
  %2 = load i32, i32* %sum, align 4
  %add = add nsw i32 %2, %mul
  store i32 %add, i32* %sum, align 4
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %3 = load i32, i32* %sum, align 4
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str, i64 0, i64 0), i32 %3)
  ret i32 0
}
