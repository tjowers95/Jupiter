#    Jupiter
  _**Find Your Frequency**_

![Jupiter's Magnetic Field](https://www.spaceanswers.com/wp-content/uploads/2014/06/Thumb.jpg)



### Problem

_**A lot of dating applications available today have developed reputations that limit the demographic**_ to first and second year college students (18-22). Beyond that age, many don't like to disclose the fact that they are on Tinder, Bumble, etc

_**No dating applications available today have addressed the anxiety associated with meeting a stranger**_, particularly in an online setting. We don't always bond with people well enough to date someone we met online. There is no oppurtunities to have a [Shared Emotional Experience](https://en.wikipedia.org/wiki/Social_sharing_of_emotions#Effect_on_relationships)

_**All dating applications available today provide minimal effort in assessing matches and guiding users**_ in the dating process

* **People need discretion**
* **People need to be taught**
* **People need to be pushed**


### Discretion
**_This is an easier obstacle_** we could use [Facebook's API to find a user's friends](https://developers.facebook.com/docs/graph-api/reference/user/friends/) and block* them from the users feed, by default. User can request to undo "Icognito".

**What if I wouldn't mind some of the girls I have as Friends on Facebook in my Jupiter Feed?** We query for the "Facebook-Friends", store that in an array on Server-Side. Each "Potential-Match" could have:
```javascript
{
...
friendsOnSocialMedia = true
}
```
That way when I'm swiping around and encounter a Facebook-Friend the picture and name is blocked and I can click "Take a chance" to request to reveal their identity if they also agree to "Take a chance". In the case that the girl that I happen to be connected with on social media has "Icognito" disabled, I would still be able to see her identity without her being able to see mine.
