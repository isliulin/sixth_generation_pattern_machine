

@echo On
 @Rem 删除SVN版本控制目录
@PROMPT [Com]

@for /r . %%a in (.) do @if exist "%%a/.svn" rd /s /q "%%a/.svn"
 @Rem for /r . %%a in (.) do @if exist "%%a/.svn" @echo "%%a/.svn"

@echo Mission Completed.
 @pause

 

@echo On
 @Rem 删除CVS版本控制目录
@PROMPT [Com]#

@for /r . %%a in (.) do @if exist "%%a/CVS" rd /s /q "%%a/CVS"
 @Rem for /r . %%a in (.) do @if exist "%%a/CVS" @echo "%%a/CVS"

@echo Mission Completed.
 @pause

 

@echo On
 @Rem 删除git版本控制目录
@PROMPT [Com]

@for /r . %%a in (.) do @if exist "%%a/.git" rd /s /q "%%a/.git"
 @Rem for /r . %%a in (.) do @if exist "%%a/.git" @echo "%%a/.git"

@echo Mission Completed.
 @pause
