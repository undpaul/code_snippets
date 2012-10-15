## on domain installations we might need a host, so we pass it at first parameter
HOST=${1}

if [ "$HOST" = "" ]
then
  DRUPAL_ROOT=$(drush status drupal-root --pipe)
else
  DRUPAL_ROOT=$(drush -l $HOST status drupal-root --pipe)
fi

# If we got a drual root, we might find the update script and execute it.
if [ ! $DRUPAL_ROOT = "" ]
then
  echo "Drupal root found: $DRUPAL_ROOT"
  if [ -f "$DRUPAL_ROOT/sites/all/scripts/update.sh" ]
  then
    echo "Executing update.sh ..."
    sh "$DRUPAL_ROOT/sites/all/scripts/update.sh"
  else
    echo "no update.sh"
  fi
else
  echo "No drupal root found."
fi

