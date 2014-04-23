#ifndef KEYWORDITEM_H
#define KEYWORDITEM_H

#include <QString>

/*
struct KeyWordItem
{
  QString id;
  QString key_word;
  QString target_url;
  QString baidu_index;
  QString ever_top;
  int     cur_rank;
};
*/

struct KeyWordItem
{
  int     click_count;
  QString task_id;
  QString key_words;
  QString url_regex;
  QString city;

};

#endif // KEYWORDITEM_H
