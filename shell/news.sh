#! /bin/sh

HOME=~
cd .

for i in `ls -t * $HOME/.news_time`
do
    case $i in
      */.news_time) break ;;
      *)            echo news: $i
    esac
done
touch $HOME/.news_time
