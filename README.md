# SpookyStoreys
![alt text](https://i.imgur.com/1yknMQ8.png)
**To use repository for development**
1. on the command line run
```
git clone https://github.com/alexchung1233/SpookyStoreys.git
```
2. to create a new development branch
```
git checkout -b [branch name]
```
Note: the branch name should describe the issue you are working on

3. to pull from the main branch
```
git pull main
```
4. to switch branches
```
git checkout main
```

5. once you committed your changes on your branch, you want to then push it to GitHub, which is where all remote branches are held.
for first time push do this
```
git push --set-upstream origin [branch your working with]
```
for general usage
```
git push
```

**To run for development enviorment.**

1. first delete the Debug directory
2. create a Debug directory
3. run this command
```
 cmake ..
```
and then
```
make
```
finally
```
./main
```

![monster](https://i.imgur.com/twIzp6u.png)
<br/>
Game demo
https://www.youtube.com/watch?v=bOaBqbG62P8
