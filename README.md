# Documentation of inLGU

## About
inLGU is a new, simple, and fantastic social media **only for LGUers**. Everyone can post, like/dislike, or even delete any messages. We aim to promote the communication among the whole campus.  

## Development

1. Recommend:

   > Python version >= 3.7
   >
   > Use [PyCharm](https://www.jetbrains.com/pycharm/download/) as IDE
   >
   > Use [Sourcetree](https://www.sourcetreeapp.com/) as version control client, and [Git-flow](https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow) as the working flow
   >
   > Use [Anaconda](https://www.anaconda.com/distribution/) as Python virtual environment manager

2. Enter the working directory, new an Python environment, install the dependencies via:
```bash
pip install -r requirements.txt
```

2. In the working directory, run the sever via:
```bash
flask run
```



## TODO

1. Basic functionality:
   1. Message:
      1. Post;
         1. Option for anonymity;
      2. Tag;
      3. Up (Like);
      4. Down;
      5. Delete;
   2. Comment:
      1. Comment on a message;
         1. Option for anonymity;
      2. Reply on a comment;
         1. Option for anonymity;
      3. Up (Like);
      4. Down;
      5. Delete;
   3. User:
      1. Login via Microsoft Graph;
      2. User system:
         1. Set/Reset password (Optional);
         2. Delete account;
         3. Change profile (bio./pic. etc.);
      3. Likes (collection);
      4. Notification (Optional);
2. ~~Find more relevant messages via tag;~~
3. Scrolling down to load more messages;

4. Support images;
5. Support pdf;
6. Support video;
7. Algorithms for message feeding;